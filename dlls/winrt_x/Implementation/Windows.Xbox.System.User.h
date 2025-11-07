#pragma once
#include "Windows.Xbox.System.User.g.h"

namespace winrt::Windows::Xbox::System::implementation
{
    struct User : UserT<User>
    {
        User() = default;
        User(uint64_t id) : m_id(id), wdcfg(WinDurangoConfig::Instance()) {}

        static winrt::Windows::Xbox::System::UserOnlineState OnlineState();
        static winrt::event_token OnlineStateChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::OnlineStateChangedEventArgs> const& handler);
        static void OnlineStateChanged(winrt::event_token const& token) noexcept;
        static winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::User> Users();
        static winrt::event_token UserAdded(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserAddedEventArgs> const& handler);
        static void UserAdded(winrt::event_token const& token) noexcept;
        static winrt::event_token UserRemoved(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserRemovedEventArgs> const& handler);
        static void UserRemoved(winrt::event_token const& token) noexcept;
        static winrt::Windows::Xbox::System::User GetUserById(uint32_t id);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> GetTokenAndSignatureForAllUsersAsync(hstring httpMethod, hstring url, hstring headers);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> GetTokenAndSignatureForAllUsersAsync(hstring httpMethod, hstring url, hstring headers, array_view<uint8_t const> body);
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> GetTokenAndSignatureForAllUsersAsync(hstring httpMethod, hstring url, hstring headers, hstring body);
        static winrt::event_token AudioDeviceAdded(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceAddedEventArgs> const& handler);
        static void AudioDeviceAdded(winrt::event_token const& token) noexcept;
        static winrt::event_token AudioDeviceRemoved(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceRemovedEventArgs> const& handler);
        static void AudioDeviceRemoved(winrt::event_token const& token) noexcept;
        static winrt::event_token AudioDeviceChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::AudioDeviceChangedEventArgs> const& handler);
        static void AudioDeviceChanged(winrt::event_token const& token) noexcept;
        static winrt::event_token SignInCompleted(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignInCompletedEventArgs> const& handler);
        static void SignInCompleted(winrt::event_token const& token) noexcept;
        static winrt::event_token SignOutStarted(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignOutStartedEventArgs> const& handler);
        static void SignOutStarted(winrt::event_token const& token) noexcept;
        static winrt::event_token SignOutCompleted(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignOutCompletedEventArgs> const& handler);
        static void SignOutCompleted(winrt::event_token const& token) noexcept;
        static winrt::event_token UserDisplayInfoChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserDisplayInfoChangedEventArgs> const& handler);
        static void UserDisplayInfoChanged(winrt::event_token const& token) noexcept;
        static winrt::guid GetNetworkCacheIdForUsers(winrt::Windows::Foundation::Collections::IVectorView<uint32_t> const& users);
        uint32_t Id();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::IAudioDeviceInfo> AudioDevices();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Input::IController> Controllers();
        winrt::Windows::Xbox::System::UserDisplayInfo DisplayInfo();
        bool IsGuest();
        bool IsSignedIn();
        winrt::Windows::Xbox::System::UserLocation Location();
        winrt::Windows::Xbox::System::User Sponsor();
        hstring XboxUserHash();
        hstring XboxUserId();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> GetTokenAndSignatureAsync(hstring httpMethod, hstring url, hstring headers);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> GetTokenAndSignatureAsync(hstring httpMethod, hstring url, hstring headers, array_view<uint8_t const> body);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Xbox::System::GetTokenAndSignatureResult> GetTokenAndSignatureAsync(hstring httpMethod, hstring url, hstring headers, hstring body);
        uint64_t m_id {0};
    private:
        inline static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserAddedEventArgs>> m_userAddedEvent;
        inline static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::UserRemovedEventArgs>> m_userRemovedEvent;
        inline static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignOutStartedEventArgs>> m_signOutStartedEvent;
        inline static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::OnlineStateChangedEventArgs>> m_onlineStateChangedEvent;
        inline static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignInCompletedEventArgs>> m_signInCompletedEvent;
		inline static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::System::SignOutCompletedEventArgs>> m_signOutCompletedEvent;
        inline static winrt::Windows::Xbox::System::User staticUser = {nullptr};
		inline static winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Xbox::System::User> staticUsers = {nullptr};
        WinDurangoConfig& wdcfg;
    };
}
namespace winrt::Windows::Xbox::System::factory_implementation
{
    struct User : UserT<User, implementation::User>
    {
    };
}
