#include "pch.h"
#include "Windows.Xbox.ApplicationModel.Core.CoreApplicationContext.h"
#include "Windows.Xbox.ApplicationModel.Core.CoreApplicationContext.g.cpp"

namespace winrt::Windows::Xbox::ApplicationModel::Core::implementation
{
    static winrt::Windows::Xbox::System::User g_currentUser{ nullptr };
    static winrt::Windows::Xbox::System::User g_previousUser{ nullptr };
    winrt::Windows::Xbox::System::User CoreApplicationContext::CurrentUser()
    {
        return g_currentUser;
    }
    winrt::Windows::Xbox::System::User winrt::Windows::Xbox::ApplicationModel::Core::implementation::CoreApplicationContext::PreviousUser()
    {
        return g_previousUser;
    }
    winrt::event_token CoreApplicationContext::CurrentUserChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void CoreApplicationContext::CurrentUserChanged(winrt::event_token const& token) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void CoreApplicationContext::SetCurrentUser(winrt::Windows::Xbox::System::User const& value)
    {
        g_previousUser = g_currentUser;
        g_currentUser = value;
		//CurrentUserChanged(winrt::event_token{});
        // Optional: fire CurrentUserChanged event here if implemented
    }
    winrt::Windows::Xbox::System::User CoreApplicationContext::CurrentSystemUser()
    {
        return g_currentUser;
    }
    winrt::event_token CoreApplicationContext::CurrentSystemUserChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler)
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
    void CoreApplicationContext::CurrentSystemUserChanged(winrt::event_token const& token) noexcept
    {
        LOG_NOT_IMPLEMENTED(); throw hresult_not_implemented();
    }
}
