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
#include "pch.h"
#include "framework.h"

#define MMDEVAPI_EXPORT(Name) __pragma(comment(linker, "/export:" #Name "=C:\\WINDOWS\\System32\\MMDevAPI." #Name))
#define MMDEVAPI_EXPORT_ORDINAL(Name, Ordinal) __pragma(comment(linker, "/export:" #Name "=C:\\WINDOWS\\System32\\MMDevAPI." #Name ",@" #Ordinal))
#define MMDEVAPI_EXPORT_ORDINAL_PRIVATE(Name, Ordinal) __pragma(comment(linker, "/export:" #Name "=C:\\WINDOWS\\System32\\MMDevAPI.#" #Ordinal ",@" #Ordinal ",NONAME"))

MMDEVAPI_EXPORT_ORDINAL_PRIVATE(CleanupDeviceAPI, 2)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(InitializeDeviceAPI, 3)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(MMDeviceCreateRegistryPropertyStore, 4)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(MMDeviceGetDeviceEnumerator, 5)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(MMDeviceGetEndpointManager, 6)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(GetClassFromEndpointId, 7)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(GetEndpointGuidFromEndpointId, 8)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(GetSessionIdFromEndpointId, 9)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(RegisterForMediaCallback, 10)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(UnregisterMediaCallback, 11)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(GenerateMediaEvent, 12)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(AETraceOutputDebugString, 13)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(MMDeviceGetPolicyConfig, 14)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(FlushDeviceTopologyCache, 15)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(GetNeverSetAsDefaultProperty, 16)
MMDEVAPI_EXPORT_ORDINAL(ActivateAudioInterfaceAsync, 17)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(GetEndpointIdFromDeviceInterfaceId, 18)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevFindMmDevProperty, 19)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetInterfacePropertyStore, 20)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetInterfaceIdFromMMDevice, 21)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetInterfaceDataFlow, 22)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetMMDeviceFromInterfaceId, 23)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetInterfaceClassGuid, 24)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetMMDeviceIdFromInterfaceId, 25)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetInstanceIdFromInterfaceId, 26)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetRelatedInterfaceId, 27)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetInterfaceIdFromMMDeviceId, 28)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetInstanceIdFromMMDeviceId, 29)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetEndpointFormFactorFromMMDeviceId, 30)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(mmdDevGetDeviceIdFromPnpInterface, 31)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(GetCategoryPath, 32)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(MMDeviceCreateRegistryPropertyStore2, 33)
MMDEVAPI_EXPORT_ORDINAL_PRIVATE(MMDeviceCreateAudioSystemEffectsPropertyStore, 34)
MMDEVAPI_EXPORT_ORDINAL(DllCanUnloadNow, 35)
MMDEVAPI_EXPORT_ORDINAL(DllGetClassObject, 36)
MMDEVAPI_EXPORT_ORDINAL(DllRegisterServer, 37)
MMDEVAPI_EXPORT_ORDINAL(DllUnregisterServer, 38)


void DisableBitstreamOut_X() {}
HRESULT EnableSpatialAudio_X() { return S_OK; }
void RestoreBitstreamOut_X() {}

DWORD_PTR __stdcall SetWasapiThreadAffinityMask_X(DWORD_PTR dwThreadAffinityMask)
{
    // Make sure the requested mask is valid for this process.
    DWORD_PTR processMask = 0, systemMask = 0;
    if (!GetProcessAffinityMask(GetCurrentProcess(), &processMask, &systemMask))
        return 0; // unexpected failure

    if ((dwThreadAffinityMask & processMask) == 0)
        dwThreadAffinityMask &= processMask;

    // Apply and return the previous affinity mask (0 on failure).
    return SetThreadAffinityMask(GetCurrentThread(), dwThreadAffinityMask);
}
void RefreshWasapiDeviceList_X() {}

