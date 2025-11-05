#include "pch.h"
#include "Microsoft.Xbox.GameChat.ChatManager.h"
#include "Microsoft.Xbox.GameChat.ChatManager.g.cpp"

namespace winrt::Microsoft::Xbox::GameChat::implementation
{
    ChatManager::ChatManager(winrt::Microsoft::Xbox::GameChat::ChatSessionPeriod const& chatSessionPeriod)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    ChatManager::ChatManager(winrt::Microsoft::Xbox::GameChat::ChatSessionPeriod const& chatSessionPeriod, bool titleEnforcedPrivilegeAndPrivacy)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    ChatManager::ChatManager(winrt::Microsoft::Xbox::GameChat::ChatSessionPeriod const& chatSessionPeriod, winrt::Microsoft::Xbox::GameChat::PrivilegeAndPrivacyEnforcementMode const& privilegeAndPrivacyEnforcementMode, winrt::Microsoft::Xbox::GameChat::TextConversionMode const& textConversionMode)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Microsoft::Xbox::GameChat::ChatManagerSettings ChatManager::ChatSettings()
    {
        return winrt::make<ChatManagerSettings>();
    }
    winrt::event_token ChatManager::OnDebugMessage(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Xbox::GameChat::DebugMessageEventArgs> const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void ChatManager::OnDebugMessage(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::event_token ChatManager::OnOutgoingChatPacketReady(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Xbox::GameChat::ChatPacketEventArgs> const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void ChatManager::OnOutgoingChatPacketReady(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::event_token ChatManager::OnCompareUniqueConsoleIdentifiers(winrt::Microsoft::Xbox::GameChat::CompareUniqueConsoleIdentifiersHandler const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void ChatManager::OnCompareUniqueConsoleIdentifiers(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::event_token ChatManager::OnUserAddedToChannel(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Xbox::GameChat::ChannelUpdatedEventArgs> const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void ChatManager::OnUserAddedToChannel(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::event_token ChatManager::OnUserRemovedFromChannel(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Xbox::GameChat::ChannelUpdatedEventArgs> const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void ChatManager::OnUserRemovedFromChannel(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::event_token ChatManager::OnPreEncodeAudioBuffer(winrt::Microsoft::Xbox::GameChat::ProcessAudioBufferHandler const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void ChatManager::OnPreEncodeAudioBuffer(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::event_token ChatManager::OnPostDecodeAudioBuffer(winrt::Microsoft::Xbox::GameChat::ProcessAudioBufferHandler const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void ChatManager::OnPostDecodeAudioBuffer(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::event_token ChatManager::OnTextMessageReceived(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Xbox::GameChat::TextMessageReceivedEventArgs> const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void ChatManager::OnTextMessageReceived(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::event_token ChatManager::OnAccessibilitySettingsChanged(winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Xbox::GameChat::AccessibilitySettingsChangedEventArgs> const& __param0)
    {
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void ChatManager::OnAccessibilitySettingsChanged(winrt::event_token const& __param0) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Microsoft::Xbox::GameChat::ChatMessageType ChatManager::ProcessIncomingChatMessage(winrt::Windows::Storage::Streams::IBuffer const& chatPacket, winrt::Windows::Foundation::IInspectable const& uniqueRemoteConsoleIdentifier)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void ChatManager::HandleNewRemoteConsole(winrt::Windows::Foundation::IInspectable const& uniqueRemoteConsoleIdentifier)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ChatManager::AddLocalUserToChatChannelAsync(uint8_t channelIndex, winrt::Windows::Xbox::System::IUser user)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ChatManager::AddLocalUsersToChatChannelAsync(uint8_t channelIndex, winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::User> users)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ChatManager::RemoveLocalUserFromChatChannelAsync(uint8_t channelIndex, winrt::Windows::Xbox::System::IUser user)
    {
        co_return;
    }
    winrt::Windows::Foundation::IAsyncAction ChatManager::RemoveRemoteConsoleAsync(winrt::Windows::Foundation::IInspectable uniqueRemoteConsoleIdentifier)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Xbox::GameChat::ChatUser> ChatManager::GetChatUsers()
    {
		return winrt::single_threaded_vector<winrt::Microsoft::Xbox::GameChat::ChatUser>().GetView();
    }
    void ChatManager::MuteUserFromAllChannels(winrt::Microsoft::Xbox::GameChat::ChatUser const& user)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void ChatManager::UnmuteUserFromAllChannels(winrt::Microsoft::Xbox::GameChat::ChatUser const& user)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void ChatManager::MuteAllUsersFromAllChannels()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void ChatManager::UnmuteAllUsersFromAllChannels()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ChatManager::MuteUserIfReputationIsBadAsync(winrt::Microsoft::Xbox::GameChat::ChatUser user)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    bool ChatManager::HasMicFocus()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    winrt::Microsoft::Xbox::GameChat::ChatPerformanceCounters ChatManager::ChatPerformanceCounters()
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
}
