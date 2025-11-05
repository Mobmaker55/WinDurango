#include "pch.h"
#include "Microsoft.Xbox.Services.UserStatistics.UserStatisticsService.h"
#include "Microsoft.Xbox.Services.UserStatistics.UserStatisticsService.g.cpp"


namespace winrt::Microsoft::Xbox::Services::UserStatistics::implementation
{
    winrt::event_token UserStatisticsService::StatisticChanged(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Xbox::Services::UserStatistics::StatisticChangeEventArgs> const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void UserStatisticsService::StatisticChanged(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::UserStatistics::UserStatisticsResult> UserStatisticsService::GetSingleUserStatisticsAsync(hstring xboxUserId, hstring serviceConfigurationId, hstring statisticName)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::UserStatistics::UserStatisticsResult> UserStatisticsService::GetSingleUserStatisticsAsync(hstring xboxUserId, hstring serviceConfigurationId, winrt::Windows::Foundation::Collections::IVectorView<hstring> statisticNames)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Xbox::Services::UserStatistics::UserStatisticsResult>> UserStatisticsService::GetMultipleUserStatisticsAsync(winrt::Windows::Foundation::Collections::IVectorView<hstring> xboxUserIds, hstring serviceConfigurationId, winrt::Windows::Foundation::Collections::IVectorView<hstring> statisticNames)
    {
		for (uint32_t i = 0; i < statisticNames.Size(); i++) {
            LOG_INFO("[UserStatisticsService] GetMultipleUserStatisticsAsync [Statistic (%u)] [%ls]\n", i, statisticNames.GetAt(i).c_str());
		}

		co_return winrt::single_threaded_vector<UserStatisticsResult>().GetView();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Xbox::Services::UserStatistics::UserStatisticsResult>> UserStatisticsService::GetMultipleUserStatisticsForMultipleServiceConfigurationsAsync(winrt::Windows::Foundation::Collections::IVectorView<hstring> xboxUserIds, winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Xbox::Services::UserStatistics::RequestedStatistics> requestedServiceConfigurationStatisticsCollection)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Microsoft::Xbox::Services::UserStatistics::StatisticChangeSubscription UserStatisticsService::SubscribeToStatisticChange(hstring const& xboxUserId, hstring const& serviceConfigurationId, hstring const& statisticName)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void UserStatisticsService::UnsubscribeFromStatisticChange(winrt::Microsoft::Xbox::Services::UserStatistics::StatisticChangeSubscription const& subscription)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
}
