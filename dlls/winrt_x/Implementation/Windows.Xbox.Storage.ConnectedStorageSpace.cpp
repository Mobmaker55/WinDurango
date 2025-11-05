#include "pch.h"
#include "Windows.Xbox.Storage.ConnectedStorageSpace.h"

#include "Windows.Xbox.Storage.ConnectedStorageContainer.h"
#include "Windows.Xbox.Storage.ConnectedStorageSpace.g.cpp"
#include "Windows.Xbox.System.Console.h"
#include "Windows.Xbox.System.User.h"
#include "Windows.Xbox.Storage.ContainerInfoQueryResult.h"

namespace winrt::Windows::Xbox::Storage::implementation
{
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetForUserAsync(winrt::Windows::Xbox::System::User user)
    {
        if (userStorageSpace == Storage::ConnectedStorageSpace(nullptr)) {
            userStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(WinDurango::impl::s_userStorage);
        }

		co_return userStorageSpace;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetForUserAsync(winrt::Windows::Xbox::System::User user, hstring serviceConfigurationId)
    {
        if (userStorageSpace == Storage::ConnectedStorageSpace(nullptr)) {
            userStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(WinDurango::impl::s_userStorage);
        }

        co_return userStorageSpace;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetForMachineAsync()
    {
        if (machineStorageSpace == Storage::ConnectedStorageSpace(nullptr)) {
            machineStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(WinDurango::impl::s_machineStorage);
        }

        co_return machineStorageSpace;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetForMachineAsync(hstring serviceConfigurationId)
    {
        if (machineStorageSpace == Storage::ConnectedStorageSpace(nullptr)) {
            machineStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(WinDurango::impl::s_machineStorage);
        }

        co_return machineStorageSpace;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetSyncOnDemandForUserAsync(winrt::Windows::Xbox::System::User user)
    {
        if (userStorageSpace == Storage::ConnectedStorageSpace(nullptr)) {
            userStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(WinDurango::impl::s_userStorage);
        }

        co_return userStorageSpace;
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::Storage::ConnectedStorageSpace> ConnectedStorageSpace::GetSyncOnDemandForUserAsync(winrt::Windows::Xbox::System::User user, hstring serviceConfigurationId)
    {
        if (userStorageSpace == Storage::ConnectedStorageSpace(nullptr)) {
            userStorageSpace = winrt::make<implementation::ConnectedStorageSpace>(WinDurango::impl::s_userStorage);
        }

        co_return userStorageSpace;
    }
    winrt::Windows::Xbox::System::User ConnectedStorageSpace::User()
    {
        return System::implementation::User::Users().GetAt(0);
    }
    hstring ConnectedStorageSpace::ServiceConfigurationId()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    bool ConnectedStorageSpace::IsReadOnly()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Storage::ConnectedStorageContainer ConnectedStorageSpace::CreateContainer(hstring const& containerName)
    {
		if (WinDurango::impl::s_userStorage == nullptr || WinDurango::impl::s_machineStorage == nullptr)
			assert("s_userStorage is null");

        if (containers == nullptr)
            containers = winrt::single_threaded_map<hstring, winrt::Windows::Xbox::Storage::ConnectedStorageContainer>();

        if (!containers.HasKey(containerName)) {
            winrt::Windows::Xbox::Storage::ConnectedStorageContainer container = winrt::make<ConnectedStorageContainer>(containerName, m_connectedStorage);

            containers.Insert(containerName, container);
            return container;
        }

		return containers.Lookup(containerName);
    }

    winrt::Windows::Foundation::IAsyncAction ConnectedStorageSpace::DeleteContainerAsync(hstring containerName)
    {
        co_await m_connectedStorage->DeleteContainer(containerName);
        containers.Remove(containerName);
    }

    winrt::Windows::Xbox::Storage::ContainerInfoQueryResult ConnectedStorageSpace::CreateContainerInfoQuery(hstring const& containerNamePrefix)
    {
        return winrt::make<winrt::Windows::Xbox::Storage::implementation::ContainerInfoQueryResult>(containerNamePrefix, m_connectedStorage);
    }
    winrt::Windows::Foundation::IAsyncOperation<int32_t> ConnectedStorageSpace::GetRemainingBytesInQuotaAsync()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<int64_t> ConnectedStorageSpace::GetRemainingBytesInQuota64Async()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
}
