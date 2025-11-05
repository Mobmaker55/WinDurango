#include "pch.h"
#include "Microsoft.Xbox.Services.Social.SocialService.h"
#include "Microsoft.Xbox.Services.Social.SocialService.g.cpp"


namespace winrt::Microsoft::Xbox::Services::Social::implementation
{
    winrt::event_token SocialService::SocialRelationshipChanged(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Xbox::Services::Social::SocialRelationshipChangeEventArgs> const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void SocialService::SocialRelationshipChanged(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::Social::XboxSocialRelationshipResult> SocialService::GetSocialRelationshipsAsync()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::Social::XboxSocialRelationshipResult> SocialService::GetSocialRelationshipsAsync(winrt::Microsoft::Xbox::Services::Social::SocialRelationship socialRelationshipFilter)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::Social::XboxSocialRelationshipResult> SocialService::GetSocialRelationshipsAsync(hstring xboxUserId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::Social::XboxSocialRelationshipResult> SocialService::GetSocialRelationshipsAsync(winrt::Microsoft::Xbox::Services::Social::SocialRelationship socialRelationshipFilter, uint32_t startIndex, uint32_t maxItems)
    {
        co_await winrt::resume_background();
    }
    winrt::Microsoft::Xbox::Services::Social::SocialRelationshipChangeSubscription SocialService::SubscribeToSocialRelationshipChange(hstring const& xboxUserId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void SocialService::UnsubscribeFromSocialRelationshipChange(winrt::Microsoft::Xbox::Services::Social::SocialRelationshipChangeSubscription const& subscription)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
}
