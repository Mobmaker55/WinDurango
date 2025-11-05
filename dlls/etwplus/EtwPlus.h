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
#ifndef EVENT_TRACKING_LOG_H
#define EVENT_TRACKING_LOG_H

#include <windows.h>
#include <evntrace.h>  // Contains EVENT_DATA_DESCRIPTOR, REGHANDLE, etc.
#include <wmistr.h>    // For WMI and ETW structures
#include "evntprov.h"  // Ensure this file is available

#define _DWORD DWORD   // Define _DWORD as DWORD (32-bit unsigned int)
#define _QWORD UINT64  // Define _QWORD as UINT64 (64-bit unsigned int)
#define BUFFER_SIZE 64  // Define a reasonable buffer size

#define DEFAULT_SAMPLE_PERCENTAGE 10


typedef enum _EventSampleRate {
    EventSample_UseProviderSample = -2,
    EventSample_UseSystemSample = -1,
    EventSample_Undefined = 0,
} EventSampleRate;

typedef enum _EventProviderLatency {
    EventProviderLatency_Undefined = 0,
    EventProviderLatency_Normal,
    EventProviderLatency_RealTime,
    EventProviderLatency_Max
} EventProviderLatency;

typedef enum _EventLatency {
    EventLatency_Undefined = 0,
    EventLatency_Normal,
    EventLatency_RealTime,
    EventLatency_DefaultProvider,
    EventLatency_Max
} EventLatency;

typedef enum _EventProviderPriority {
    EventProviderPriority_Undefined = 0,
    EventProviderPriority_Normal,
    EventProviderPriority_Critical,
    EventProviderPriority_Max
} EventProviderPriority;

typedef enum _EventPriority {
    EventPriority_Undefined = 0,
    EventPriority_Normal,
    EventPriority_Critical,
    EventPriority_DefaultProvider,
    EventPriority_Max
} EventPriority;

typedef enum _ProviderState {
    ProviderState_Undefined = 0,
    ProviderState_ForceOff,
    ProviderState_Disabled,
    ProviderState_Enabled,
    ProviderState_ForceOn,
    ProviderState_Max
} ProviderState;

typedef enum _EventState {
    EventState_Undefined = 0,
    EventState_Disabled,
    EventState_DefaultProvider,
    EventState_Enabled,
    EventState_Max
} EventState;

typedef struct _FIELD_DESCRIPTOR {
    UINT8 Type : 5;
    UINT8 IsLengthField : 1;
} FIELD_DESCRIPTOR;


typedef struct _EVENT_DESCRIPTOR_STRUCT {
    const EVENT_DESCRIPTOR BaseDescriptor;
    LPCSTR EventName;
    LPCSTR SchemaVersion;
    const FIELD_DESCRIPTOR* FieldDescriptors;
    UINT8 FieldCount;
    UINT8 UploadEnabled;
    UINT8 CurrentUploadState;
    UINT8 DefaultUploadState;
    INT8 CurrentSampleRate;
    INT8 DefaultSampleRate;
    UINT8 CurrentLatency;
    UINT8 DefaultLatency;
    UINT8 CurrentPriority;
    UINT8 DefaultPriority;
} EVENT_DESCRIPTOR_STRUCT, * PEVENT_DESCRIPTOR_STRUCT;

typedef struct _EVENT_PROVIDER_DESCRIPTOR {
    LPCSTR ProviderName;
    const GUID ProviderGuid;
    UINT32 EventCount;
    EVENT_DESCRIPTOR_STRUCT* EventDescriptors;
    UINT8 UploadEnabled;
    UINT8 CurrentUploadState;
    UINT8 DefaultUploadState;
    INT8 CurrentSampleRate;
    INT8 DefaultSampleRate;
    UINT8 CurrentLatency;
    UINT8 DefaultLatency;
    UINT8 CurrentPriority;
    UINT8 DefaultPriority;
} EVENT_PROVIDER_DESCRIPTOR, * PEVENT_PROVIDER_DESCRIPTOR;

typedef enum _UserIdType {
    UserIdType_Xuid = 1,
    UserIdType_LiveId,
    UserIdType_LiveAnid,
    UserIdType_Anonymous
} UserIdType;

VOID __stdcall EtxFillCommonFields_v7_X(EVENT_DATA_DESCRIPTOR* eventDataDescriptors,
    UINT8* buffer, UINT32 bufferSize);

ULONG __stdcall EtxRegister_X(EVENT_PROVIDER_DESCRIPTOR* provider, REGHANDLE* handle);

ULONG __stdcall EtxUnregister_X(EVENT_PROVIDER_DESCRIPTOR* provider, REGHANDLE* handle);

ULONG __stdcall EtxEventWrite_X(
    const EVENT_DESCRIPTOR_STRUCT* eventDescriptor,
    const EVENT_PROVIDER_DESCRIPTOR* /*providerDescriptor*/,
    REGHANDLE                        handle,
    ULONG                            dataCount,
    const EVENT_DATA_DESCRIPTOR* eventData);

void __stdcall EtxSuspendUploading_X();

void __stdcall EtxResumeUploading_X();
#pragma warning(pop)
#endif // EtwPlus_H