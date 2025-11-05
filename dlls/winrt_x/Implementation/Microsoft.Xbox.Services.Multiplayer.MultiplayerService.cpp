#include "pch.h"
#include "Microsoft.Xbox.Services.Multiplayer.MultiplayerService.h"
#include "Microsoft.Xbox.Services.Multiplayer.MultiplayerService.g.cpp"


namespace winrt::Microsoft::Xbox::Services::Multiplayer::implementation
{
    winrt::event_token MultiplayerService::MultiplayerSessionChanged(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionChangeEventArgs> const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void MultiplayerService::MultiplayerSessionChanged(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::event_token MultiplayerService::MultiplayerSubscriptionLost(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSubscriptionLostEventArgs> const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void MultiplayerService::MultiplayerSubscriptionLost(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSession> MultiplayerService::WriteSessionAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSession multiplayerSession, winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionWriteMode multiplayerSessionWriteMode)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::Multiplayer::WriteSessionResult> MultiplayerService::TryWriteSessionAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSession multiplayerSession, winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionWriteMode multiplayerSessionWriteMode)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSession> MultiplayerService::WriteSessionByHandleAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSession multiplayerSession, winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionWriteMode multiplayerSessionWriteMode, hstring handleId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::Multiplayer::WriteSessionResult> MultiplayerService::TryWriteSessionByHandleAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSession multiplayerSession, winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionWriteMode multiplayerSessionWriteMode, hstring handleId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSession> MultiplayerService::GetCurrentSessionAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionReference sessionReference)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSession> MultiplayerService::GetCurrentSessionByHandleAsync(hstring handleId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionStates>> MultiplayerService::GetSessionsAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerGetSessionsRequest getSessionsRequest)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionStates>> MultiplayerService::GetSessionsAsync(hstring serviceConfigurationId, hstring sessionTemplateNameFilter, hstring xboxUserIdFilter, hstring keywordFilter, winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionVisibility visibilityFilter, uint32_t contractVersionFilter, bool includePrivateSessions, bool includeReservations, bool includeInactiveSessions, uint32_t maxItems)
    {
        co_await winrt::resume_background();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionStates>> MultiplayerService::GetSessionsForUsersFilterAsync(hstring serviceConfigurationId, hstring sessionTemplateNameFilter, winrt::Windows::Foundation::Collections::IVectorView<hstring> xboxUserIdsFilter, hstring keywordFilter, winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionVisibility visibilityFilter, uint32_t contractVersionFilter, bool includePrivateSessions, bool includeReservations, bool includeInactiveSessions, uint32_t maxItems)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction MultiplayerService::SetActivityAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionReference sessionReference)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<hstring> MultiplayerService::SetTransferHandleAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionReference targetSessionReference, winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionReference originSessionReference)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction MultiplayerService::SetSearchHandleAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSearchHandleRequest searchHandleRequest)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction MultiplayerService::ClearActivityAsync(hstring serviceConfigurationId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction MultiplayerService::ClearSearchHandleAsync(hstring handleId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<hstring>> MultiplayerService::SendInvitesAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionReference sessionReference, winrt::Windows::Foundation::Collections::IVectorView<hstring> xboxUserIds, uint32_t titleId)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<hstring>> MultiplayerService::SendInvitesAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSessionReference sessionReference, winrt::Windows::Foundation::Collections::IVectorView<hstring> xboxUserIds, uint32_t titleId, hstring contextStringId, hstring activationContext)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerActivityDetails>> MultiplayerService::GetActivitiesForSocialGroupAsync(hstring serviceConfigurationId, hstring socialGroupOwnerXboxUserId, hstring socialGroup)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerActivityDetails>> MultiplayerService::GetActivitiesForUsersAsync(hstring serviceConfigurationId, winrt::Windows::Foundation::Collections::IVectorView<hstring> xboxUserIds)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSearchHandleDetails>> MultiplayerService::GetSearchHandlesAsync(hstring serviceConfigurationId, hstring sessionTemplateName, hstring orderBy, bool orderAscending, hstring searchFilter)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerSearchHandleDetails>> MultiplayerService::GetSearchHandlesAsync(winrt::Microsoft::Xbox::Services::Multiplayer::MultiplayerQuerySearchHandleRequest searchHandleRequest)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void MultiplayerService::EnableMultiplayerSubscriptions()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void MultiplayerService::DisableMultiplayerSubscriptions()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    bool MultiplayerService::MultiplayerSubscriptionsEnabled()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
}
