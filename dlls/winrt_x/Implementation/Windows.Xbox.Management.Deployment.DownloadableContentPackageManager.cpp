#include "pch.h"
#include "Windows.Xbox.Management.Deployment.DownloadableContentPackageManager.h"
#include "Windows.Xbox.Management.Deployment.DownloadableContentPackageManager.g.cpp"

namespace winrt::Windows::Xbox::Management::Deployment::implementation
{
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Management::Deployment::IDownloadableContentPackage> DownloadableContentPackageManager::FindPackages(winrt::Windows::Xbox::Management::Deployment::InstalledPackagesFilter const& filter)
    {
        return winrt::single_threaded_vector<winrt::Windows::Xbox::Management::Deployment::IDownloadableContentPackage>().GetView();
    }
    winrt::event_token DownloadableContentPackageManager::DownloadableContentPackageInstallCompleted(winrt::Windows::Xbox::Management::Deployment::DownloadableContentPackageInstallCompletedEventHandler const& handler)
    {
        return m_downloadableContentPackageInstallCompleted.add(handler);
    }
    void DownloadableContentPackageManager::DownloadableContentPackageInstallCompleted(winrt::event_token const& eventCookie) noexcept
    {
        m_downloadableContentPackageInstallCompleted.remove(eventCookie);
    }
    winrt::event_token DownloadableContentPackageManager::DownloadableContentPackageInstallCompletedWithDetails(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Management::Deployment::IDownloadableContentPackageInstallCompletedEventArgs> const& eventHandler)
    {
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void DownloadableContentPackageManager::DownloadableContentPackageInstallCompletedWithDetails(winrt::event_token const& eventCookie) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
}
