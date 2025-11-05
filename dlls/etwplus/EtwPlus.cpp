/*
================================================================================
DISCLAIMER AND LICENSE REQUIREMENT

This code is provided with the condition that if you use, modify, or distribute
this code in your project, you are required to make your project open source
under a license compatible with the GNU General Public License (GPL) or a
similarly strong copyleft license.

By using this code, you agree to:
1. Disclose your complete source code of any project incorporating this code.
2. Include this disclaimer in any copies or substantial portions of this file.
3. Provide clear attribution to the original author.

If you do not agree to these terms, you do not have permission to use this code.

================================================================================
*/
#include "EtwPlus.h"
#include "pch.h"
#include <stdio.h>
#include "../common/Logger.h"
#include <evntrace.h>

#pragma comment(lib, "advapi32.lib")
std::atomic_bool g_EtxUploadPaused{ false };
HANDLE           g_EtxUploaderResumeEvent = nullptr;

VOID __stdcall EtxFillCommonFields_v7_X(
    EVENT_DATA_DESCRIPTOR* eventDataDescriptors,
    UINT8* buffer,
    UINT32 bufferSize)
{
	LOG_INFO("[EtxFillCommonFields_v7_X] Filling common fields in ETW event data.\n");
    // Basic validation – if something’s wrong, just bail out silently.
    if (!eventDataDescriptors || !buffer || bufferSize < 64)
        return;

    // Wipe the scratch buffer so any unused bytes are zero-filled.
    SecureZeroMemory(buffer, bufferSize);

    // Layout for the common fields block.
    struct CommonFieldsV7
    {
        ULONGLONG Timestamp;   // QueryPerformanceCounter value
        ULONG     ProcessId;   // GetCurrentProcessId()
        ULONG     ThreadId;    // GetCurrentThreadId()
        ULONG     CpuId;       // GetCurrentProcessorNumber()
        ULONG     Reserved;    // Padding / future use
    };

    static_assert(sizeof(CommonFieldsV7) <= 64, "Scratch buffer too small");

    // Populate the fields.
    auto* fields = reinterpret_cast<CommonFieldsV7*>(buffer);

    LARGE_INTEGER qpc;
    QueryPerformanceCounter(&qpc);
    fields->Timestamp = static_cast<ULONGLONG>(qpc.QuadPart);
    fields->ProcessId = GetCurrentProcessId();
    fields->ThreadId = GetCurrentThreadId();
    fields->CpuId = GetCurrentProcessorNumber();
    fields->Reserved = 0;

    // Point the first descriptor at the filled-in buffer.
    EventDataDescCreate(eventDataDescriptors, buffer, sizeof(CommonFieldsV7));
}

// Function to register an event provider
ULONG __stdcall EtxRegister_X(EVENT_PROVIDER_DESCRIPTOR* provider, REGHANDLE* handle)
{
    if (!provider || !handle)
        return ERROR_INVALID_PARAMETER;

    const GUID* providerGuid = reinterpret_cast<const GUID*>(provider);

    // No enable callback or context needed for basic registration.
    return EventRegister(providerGuid, nullptr, nullptr, handle);
}

ULONG __stdcall EtxUnregister_X(EVENT_PROVIDER_DESCRIPTOR* provider, REGHANDLE* handle)
{
    if (!provider || !handle)
        return ERROR_INVALID_PARAMETER;

    ULONG status = ERROR_SUCCESS;

    if (*handle)
    {
        status = EventUnregister(*handle);
        *handle = 0;
    }
    return status;
}

ULONG __stdcall EtxEventWrite_X(
    const EVENT_DESCRIPTOR_STRUCT* eventDescriptor,
    const EVENT_PROVIDER_DESCRIPTOR* /*providerDescriptor*/,
    REGHANDLE                        handle,
    ULONG                            dataCount,
    const EVENT_DATA_DESCRIPTOR* eventData)
{
    if (!eventDescriptor || handle == 0 || (dataCount && !eventData))
        return ERROR_INVALID_PARAMETER;

    const auto* desc = reinterpret_cast<const EVENT_DESCRIPTOR*>(eventDescriptor);

    // EventWrite needs a non-const pointer for the data array
    return EventWrite(
        handle,
        desc,
        dataCount,
        const_cast<PEVENT_DATA_DESCRIPTOR>(eventData));
}

void __stdcall EtxSuspendUploading_X()
{
    g_EtxUploadPaused.store(true, std::memory_order_release);

    if (g_EtxUploaderResumeEvent)
        ResetEvent(g_EtxUploaderResumeEvent);
}

void __stdcall EtxResumeUploading_X()
{
    // Clear the pause flag
    g_EtxUploadPaused.store(false, std::memory_order_release);

    // Wake any uploader thread waiting on the resume event
    if (g_EtxUploaderResumeEvent)
        SetEvent(g_EtxUploaderResumeEvent);
}
