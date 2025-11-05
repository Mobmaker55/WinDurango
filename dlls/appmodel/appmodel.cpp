// appmodel.cpp : Defines the exported functions for the DLL.
#include "pch.h"
#include "appmodel.h"
#include <stdlib.h>
#include <hstring.h>
#include <strsafe.h>
#include <string>
#include <vector>
#include "../common/Logger.h"

CRITICAL_SECTION CriticalSection;
__int64 qword_18009E948 = 0;

struct _XBOX_LIVE_TITLE_INFO {
    DWORD TitleId;
    GUID PrimaryServiceConfigId;
    DWORD RequireXboxLive;
};
namespace AppModel {
    namespace Runtime {
        LSTATUS __fastcall EnumerateKeyNames(HKEY hKey, std::vector<std::wstring>& keyNames)
        {
            if (!hKey)
                return ERROR_INVALID_PARAMETER;

            keyNames.clear();
            DWORD index = 0;
            WCHAR nameBuffer[ 256 ] = { 0 };
            DWORD nameSize;
            LSTATUS result;

            while (true)
            {
                nameSize = ARRAYSIZE(nameBuffer);
                result = RegEnumKeyExW(hKey, index, nameBuffer, &nameSize, nullptr, nullptr, nullptr, nullptr);

                if (result != ERROR_SUCCESS)
                    break;

                keyNames.emplace_back(nameBuffer);
                ++index;
            }

            return (result == ERROR_NO_MORE_ITEMS) ? ERROR_SUCCESS : result;
        }
        __int64 __fastcall GetCurrentPackageFullName_X(std::wstring& packageFullName)
        {
			LOG_DEBUG("GetCurrentPackageFullName %s", packageFullName);
            packageFullName.clear();
            //if ((NtCurrentPeb()->BitField & 0x20) == 0)
            //    return 15700;

            HKEY hKey = nullptr;
            LSTATUS status = RegOpenKeyExW(
                HKEY_LOCAL_MACHINE,
                L"XBOX\Software\Microsoft\Windows\CurrentVersion\AppModel\Repository\Families",
                0,
                KEY_READ,
                &hKey);

            if (status == ERROR_SUCCESS)
            {
                std::vector<std::wstring> familyKeys;
                status = EnumerateKeyNames(hKey, familyKeys);
                if (status == ERROR_SUCCESS && !familyKeys.empty())
                {
                    HKEY phkResult = nullptr;
                    status = RegOpenKeyExW(hKey, familyKeys[ 0 ].c_str(), 0, KEY_READ, &phkResult);
                    if (status == ERROR_SUCCESS)
                    {
                        std::vector<std::wstring> packageKeys;
                        status = EnumerateKeyNames(phkResult, packageKeys);
                        if (status == ERROR_SUCCESS && !packageKeys.empty())
                        {
                            packageFullName = packageKeys[ 0 ];
                        }
                        else
                        {
                            status = 1168;
                        }
                        RegCloseKey(phkResult);
                    }
                }
                else
                {
                    status = 1168;
                }
                RegCloseKey(hKey);
            }

            return status;
        }
        __int64 __fastcall GetPackagesByPackageFamily_X(LPCWSTR lpSubKey, std::vector<std::wstring>& packageList)
        {
			LOG_DEBUG("GetPackagesByPackageFamily_X %s", lpSubKey ? lpSubKey : L"nullptr");
            if (lpSubKey == nullptr)
                return ERROR_INVALID_PARAMETER;

            packageList.clear();
            HKEY hKey = nullptr;
            HKEY phkResult = nullptr;

            LSTATUS status = RegOpenKeyExW(
                HKEY_LOCAL_MACHINE,
                L"XBOX\\Software\\Microsoft\\Windows\\CurrentVersion\\AppModel\\Repository\\Families",
                0,
                KEY_READ,
                &hKey);

            if (status == ERROR_SUCCESS)
            {
                status = RegOpenKeyExW(hKey, lpSubKey, 0, KEY_READ, &phkResult);
                if (status == ERROR_SUCCESS)
                {
                    status = EnumerateKeyNames(phkResult, packageList);
                    RegCloseKey(phkResult);
                }
                RegCloseKey(hKey);
            }

            return status;
        }
    }
}
struct _PSM_APPSTATE_REGISTRATION {
    CONDITION_VARIABLE CallbackFinished;
    _LIST_ENTRY Entry;
    BYTE Flags;
};

class PsmCli {
public:
    static int EnsureInitialized(PsmCli* instance) {
        return instance ? 0 : -1;
    }
    static void UnregisterAppStateChangeNotification(PsmCli* instance, _PSM_APPSTATE_REGISTRATION* registration);
};
class ModuleBase {
public:
    static ModuleBase* module_;
    bool CanUnloadNow() const {
        return true;
    }
};
ModuleBase* ModuleBase::module_ = nullptr;

HRESULT __stdcall DllCanUnloadNow_X()
{
    static ModuleBase moduleInstance;
    static bool initialized = false;

    if (!initialized) {
        ModuleBase::module_ = &moduleInstance;
        atexit([]() { ModuleBase::module_ = nullptr; });
        initialized = true;
    }

    return (moduleInstance.CanUnloadNow()) ? S_OK : S_FALSE;
}
HRESULT CreateRandomAccessStreamOnFile_X(PCWSTR filePath, DWORD accessMode, REFIID riid, void** ppv) { return TRUE; }

HRESULT CreateRandomAccessStreamOverStream_X(
    // IStream      *stream,
    // BSOS_OPTIONS options,
    REFIID       riid,
    void** ppv)
{
    return TRUE;
}



__int64 __fastcall DllGetActivationFactory_X(HSTRING string, PVOID Ptr)
{
    LOG_NOT_IMPLEMENTED(); return 0;
}

HRESULT __stdcall DllGetClassObject_X(const IID* const rclsid, const IID* const riid, LPVOID* ppv)
{
    LOG_NOT_IMPLEMENTED();    return 0;
}

LONG __stdcall GetApplicationUserModelId_X(
        HANDLE hProcess,
        UINT32* applicationUserModelIdLength,
        PWSTR applicationUserModelId)
{
    
    return GetCurrentApplicationUserModelId_X(applicationUserModelIdLength, applicationUserModelId);
}

__int64 __fastcall GetApplicationXboxLiveInfo_X(WCHAR* a1, int a2, void* a3, unsigned int a4)
{
    
    return 0;
}

LONG __stdcall GetCurrentApplicationUserModelId_X(UINT32* applicationUserModelIdLength, PWSTR applicationUserModelId)
{
    
    return 0;
}

LONG __stdcall GetCurrentPackageFamilyName_X(UINT32* packageFamilyNameLength, PWSTR packageFamilyName)
{
    
    return 0;
}

LONG __stdcall GetCurrentPackageFullName_X(UINT32* packageFullNameLength, PWSTR packageFullName)
{
    
    LONG CurrentPackageFullName; // edi
    UINT32 v5; // edi
    const wchar_t* v6; // r8
    wchar_t* Source[ 2 ]; // [rsp+20h] [rbp-48h] BYREF
    __int64 v9; // [rsp+30h] [rbp-38h]
    unsigned __int64 v10; // [rsp+38h] [rbp-30h]

    if (!packageFullNameLength || *packageFullNameLength && !packageFullName)
        return 87;
    v10 = 7;
    v9 = 0;
    LOWORD(Source[ 0 ]);
    CurrentPackageFullName = AppModel::Runtime::GetCurrentPackageFullName_X((std::wstring&) Source);
    if (!CurrentPackageFullName)
    {
        v5 = v9 + 1;
        if (*packageFullNameLength >= (int) v9 + 1)
        {
            v6 = (const wchar_t*) Source;
            if (v10 >= 8)
                v6 = Source[ 0 ];
            wcsncpy_s(packageFullName, *packageFullNameLength, v6, 0xFFFFFFFFFFFFFFFFui64);
            *packageFullNameLength = v5;
            CurrentPackageFullName = 0;
        }
        else
        {
            *packageFullNameLength = v5;
            CurrentPackageFullName = 122;
        }
    }
    if (v10 >= 8)
    {
        if (Source[ 0 ])
        {
            //XMemFree(Source[ 0 ], qword_18009E948); look into this later
        }

    }
    return CurrentPackageFullName;
}

LONG __stdcall GetCurrentPackageId_X(UINT32* bufferLength, BYTE* buffer)
{
    
    return 0;
}


LONG __stdcall GetCurrentPackagePath_X(UINT32* pathLength, PWSTR path)
{
    
    return 0;
}



LONG __stdcall GetPackageFamilyName_X(HANDLE hProcess, UINT32* packageFamilyNameLength, PWSTR packageFamilyName)
{
    
    return GetCurrentPackageFamilyName_X(packageFamilyNameLength, packageFamilyName);
}

LONG __stdcall GetPackagePath_X(const PVOID* packageId, const UINT32 reserved, UINT32* pathLength, PWSTR path)
{
    
    return GetCurrentPackagePath_X(pathLength, path);
}

void GetPackageXboxLiveInfo_X() {  }

void GetProcessXboxLiveInfo_X() {  }

void GetXboxLiveTitleId_X() {  }

void PsmBlockAppStateChangeCompletion_X() {  }

void PsmRegisterAppStateChangeNotification_X() {  }

void PsmShutdownApplication_X() {  }

void PsmUnblockAppStateChangeCompletion_X() {  }

void PsmWaitForAppResume_X() {  }

LONG __stdcall GetPackageId(HANDLE hProcess, UINT32* bufferLength, BYTE* buffer)
{
    
    return GetCurrentPackageId_X(bufferLength, buffer);
}

LONG __stdcall GetPackageFullName_X(HANDLE hProcess, UINT32* packageFullNameLength, PWSTR packageFullName)
{
    
    return GetCurrentPackageFullName_X(packageFullNameLength, packageFullName);
}

LONG GetCurrentPackageInfo_X(const UINT32 flags, UINT32* bufferLength, BYTE* buffer, UINT32* count) {  return 0; }

LONG __stdcall GetPackagesByPackageFamily_X(
    PCWSTR packageFamilyName,
    UINT32* count,
    PWSTR* packageFullNames,
    UINT32* bufferLength,
    WCHAR* buffer)
{
    
    if (!packageFamilyName || !count || !bufferLength || (*count && !packageFullNames) || (*bufferLength && !buffer))
        return ERROR_INVALID_PARAMETER;

    std::vector<std::wstring> packageList;
    LONG status = AppModel::Runtime::GetPackagesByPackageFamily_X(packageFamilyName, packageList);
    if (status != ERROR_SUCCESS)
        return status;

    size_t requiredBufferSize = 0;
    for (const auto& package : packageList)
        requiredBufferSize += package.size() + 1;

    if (*bufferLength < requiredBufferSize)
    {
        *bufferLength = static_cast<UINT32>(requiredBufferSize);
        return ERROR_INSUFFICIENT_BUFFER;
    }

    if (*count < packageList.size())
    {
        *count = static_cast<UINT32>(packageList.size());
        return ERROR_INSUFFICIENT_BUFFER;
    }

    WCHAR* currentBufferPosition = buffer;
    for (size_t i = 0; i < packageList.size(); ++i)
    {
        wcsncpy_s(currentBufferPosition, *bufferLength - (currentBufferPosition - buffer), packageList[ i ].c_str(), packageList[ i ].size());
        packageFullNames[ i ] = currentBufferPosition;
        currentBufferPosition += packageList[ i ].size() + 1;
    }

    *count = static_cast<UINT32>(packageList.size());
    *bufferLength = static_cast<UINT32>(currentBufferPosition - buffer);
    return ERROR_SUCCESS;
}

_int64 __fastcall GetCurrentXboxLiveTitleId_X(int* a1)
{
    
    int v4[ 6 ]; // [rsp+20h] [rbp-28h] BYREF

    int v1 = 0;
    if (!a1)
        return ERROR_INVALID_PARAMETER;
    __int64 result = GetCurrentXboxLiveInfo_X(0, v4, 24);
    if (!result)
        v1 = v4[ 0 ];
    *a1 = v1;
    return result;
}
__int64 __fastcall GetSystemXboxLiveInfo_X(int a1, void* a2, unsigned int a3)
{
    
    return 0;
}
LONG __fastcall GetCurrentXboxLiveInfo_X(unsigned int a1, void* a2, unsigned int a3)
{
    
    LONG result; // eax
    HMODULE ModuleHandleW; // rax
    UINT32 applicationUserModelIdLength[ 4 ]; // [rsp+20h] [rbp-138h] BYREF
    WCHAR applicationUserModelId[ 136 ]; // [rsp+30h] [rbp-128h] BYREF

    if (!a2 || !a3)
        return 87;
    applicationUserModelIdLength[ 0 ] = 130;
    result = GetCurrentApplicationUserModelId_X(applicationUserModelIdLength, applicationUserModelId);
    if (result == 15703)
    {
        ModuleHandleW = GetModuleHandleW(0);
        if (a1 == 1)
        {
            result = GetSystemXboxLiveInfo_X(1, a2, a3);
        }
        else if (a1)
        {
            result = 50;
        }
        else
        {
            result = XblRegReadModuleTitleInfo_X(ModuleHandleW, 0, a2, a3);
        }
        if (result == 2)
            return 1168;
    }
    else if (!result)
    {
        return GetApplicationXboxLiveInfo_X(applicationUserModelId, a1, a2, a3);
    }
    return result;
}
LSTATUS __fastcall XblRegReadValue_X(HKEY hKey, LPCWSTR valueName, int expectedType, void* buffer, unsigned int bufferSize)
{
    
    DWORD dataType = 0;
    DWORD dataSize = bufferSize;

    LSTATUS result = RegQueryValueExW(hKey, valueName, 0, &dataType, reinterpret_cast<LPBYTE>(buffer), &dataSize);
    if (result == ERROR_SUCCESS && (dataType != static_cast<DWORD>(expectedType) || dataSize != bufferSize))
    {
        return ERROR_INVALID_DATA;
    }
    return result;
}
__int64 __fastcall XblRegReadModuleTitleInfo_X(HINSTANCE a1, const unsigned __int16* a2, void* a3, unsigned int a4)
{
    unsigned int result;
    HKEY hKey = nullptr;
    int useSystemTitleId = 0;

    if (a4 < 0x18)
        return ERROR_INSUFFICIENT_BUFFER;

    memset(a3, 0, 0x18);
    result = XblRegOpenModuleKey_X(a1, 0, &hKey);

    if (result == ERROR_SUCCESS) {
        if (XblRegReadValue_X(hKey, L"UseSystemTitleId", REG_DWORD, &useSystemTitleId, sizeof(useSystemTitleId)) != ERROR_SUCCESS || !useSystemTitleId) {
            result = XblRegReadTitleInfo_X(hKey, static_cast<_XBOX_LIVE_TITLE_INFO*>(a3));
        }
        else {
            result = GetSystemXboxLiveInfo_X(0, a3, a4);
        }
        RegCloseKey(hKey);
    }

    return result;
}
LSTATUS __fastcall XblRegReadTitleInfo_X(HKEY a1, struct _XBOX_LIVE_TITLE_INFO* TitleInfo)
{
	LOG_DEBUG("XblRegReadTitleInfo_X called with a1: %p", a1);
    LSTATUS result; // eax

    result = XblRegReadValue_X(a1, L"TitleId", 4, TitleInfo, 4u);
    if (!result)
    {
        result = XblRegReadValue_X(a1, L"PrimaryServiceConfigId", 3, &TitleInfo->PrimaryServiceConfigId, 0x10u);
        if (!result)
        {
            result = XblRegReadValue_X(a1, L"RequireXboxLive", 4, &TitleInfo->RequireXboxLive, 4u);
            if (result == 2)
            {
                TitleInfo->RequireXboxLive = 0;
                return 0;
            }
        }
    }
    return result;
}

__int64 __fastcall XblRegOpenModuleKey_X(HMODULE a1, __int64 a2, HKEY* a3)
{
	LOG_DEBUG("XblRegOpenModuleKey_X called with a1: %p, a2: %lld", a1, a2);
    unsigned int v4 = 1359;
    WCHAR Filename[ 264 ] = { 0 };
    WCHAR SubKey[ 512 ] = { 0 };

    if (a1 && GetModuleFileNameW(a1, Filename, 0x104))
    {
        for (WCHAR* i = Filename; *i; ++i)
        {
            unsigned __int16 v6 = *i - 46;
            if (v6 <= 0x2E)
            {
                __int64 v7 = 0x400000001003;
                if (_bittest64(&v7, v6))
                    *i = L'_';
            }
        }
        if (SUCCEEDED(StringCchPrintfW(SubKey, 0x200, L"XBOX\\Software\\Microsoft\\Windows\\CurrentVersion\\XboxLive\\TitleIds\\%s", Filename)))
            return RegOpenKeyExW(HKEY_LOCAL_MACHINE, SubKey, 0, KEY_READ, a3);
    }
    else
    {
        return ERROR_INVALID_PARAMETER;
    }
    return v4;
}

void __fastcall PsmCli::UnregisterAppStateChangeNotification(PsmCli* instance, struct _PSM_APPSTATE_REGISTRATION* a2)
{
	LOG_DEBUG("PsmCli::UnregisterAppStateChangeNotification called");
    _LIST_ENTRY* Flink;
    _LIST_ENTRY* Blink;

    if (PsmCli::EnsureInitialized(instance) >= 0)
    {
        EnterCriticalSection(&CriticalSection);
        a2->Flags |= 2u;

        if ((a2->Flags & 1) != 0)
        {
            do
                SleepConditionVariableCS(&a2->CallbackFinished, &CriticalSection, INFINITE);
            while ((a2->Flags & 1) != 0);
        }
        else
        {
            Flink = a2->Entry.Flink;
            Blink = a2->Entry.Blink;

            if (reinterpret_cast<_PSM_APPSTATE_REGISTRATION*>(Flink->Blink) != a2 ||
                reinterpret_cast<_PSM_APPSTATE_REGISTRATION*>(Blink->Flink) != a2)
            {
                __fastfail(3);
            }

            Blink->Flink = Flink;
            Flink->Blink = Blink;
            a2->Entry.Flink = nullptr;
            a2->Entry.Blink = nullptr;
        }

        LeaveCriticalSection(&CriticalSection);
        HeapFree(GetProcessHeap(), 0, a2);
    }
}

void __fastcall PsmUnregisterAppStateChangeNotification_X(struct _PSM_APPSTATE_REGISTRATION* a1)
{
    LOG_NOT_IMPLEMENTED();
    if (a1)
        PsmCli::UnregisterAppStateChangeNotification(reinterpret_cast<PsmCli*>(a1), a1);
}