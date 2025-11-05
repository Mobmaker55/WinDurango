#include "pch.h"
#include "Windows.Xbox.Input.Controller.h"
#include "Windows.Xbox.Input.Controller.g.cpp"
#include "Windows.Xbox.System.User.h"
#include "Windows.Xbox.Input.Gamepad.h"
#include <Xinput.h>

namespace winrt::Windows::Xbox::Input::implementation
{
    IController newController;
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Input::IController> Controller::Controllers()
    {
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Xbox::Input::IController> vector = winrt::single_threaded_vector<Input::IController>();

        for (IGamepad gamepad : Gamepad::Gamepads())
        {
            vector.Append(static_cast<IController>(gamepad));
        }

        return vector.GetView();
    }
    winrt::event_token Controller::ControllerAdded(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::ControllerAddedEventArgs> const& handler)
    {
        LOG_INFO_W(L"Controller || Controller Added!\n");
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void Controller::ControllerAdded(winrt::event_token const& token) noexcept
    {
        LOG_INFO_W(L"Controller || Controller Added!\n");
        throw hresult_not_implemented();
    }
    winrt::event_token Controller::ControllerRemoved(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::ControllerRemovedEventArgs> const& handler)
    {
        LOG_INFO_W(L"Controller || Controller Removed!\n");
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void Controller::ControllerRemoved(winrt::event_token const& token) noexcept
    {
        LOG_INFO_W(L"Controller || Controller Removed!\n");
        throw hresult_not_implemented();
    }
    winrt::event_token Controller::ControllerPairingChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::ControllerPairingChangedEventArgs> const& handler)
    {
        LOG_INFO_W(L"Controller || ControllerPairingChanged!\n");
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void Controller::ControllerPairingChanged(winrt::event_token const& token) noexcept
    {
        LOG_INFO_W(L"Controller || ControllerPairingChanged!\n");
        throw hresult_not_implemented();
    }
    winrt::event_token Controller::ControllerOrderChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Xbox::Input::ControllerOrderChangedEventArgs> const& handler)
    {
        LOG_INFO_W(L"Controller || ControllerOrderChanged!\n");
        LOG_NOT_IMPLEMENTED(); return {};
    }
    void Controller::ControllerOrderChanged(winrt::event_token const& token) noexcept
    {
        LOG_INFO_W(L"Controller || ControllerOrderChanged!\n");
        throw hresult_not_implemented();
    }
    winrt::Windows::Xbox::Input::IController Controller::GetControllerById(uint64_t controllerId)
    {
        LOG_INFO_W(L"Controller || GetControllerById!\n");
        return newController;
    }
    void Controller::GetControllerMetadata(uint64_t controllerId, winrt::Windows::Xbox::Input::MetadataVersion const& metadataVersion, com_array<uint8_t>& ppMetadata)
    {
        LOG_INFO_W(L"Controller || GetControllerMetadata!\n");
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::Input::IController> Controller::GetControllersOrderedLeftToRight(winrt::Windows::Xbox::Input::ControllerOrderFilter const& orderFilter)
    {
        LOG_INFO_W(L"Controller || GetControllersOrderedLeftToRight!\n");
        LOG_NOT_IMPLEMENTED(); return {};
        
    }
    uint64_t Controller::Id()
    {
        LOG_NOT_IMPLEMENTED(); return 0;
    }
    hstring Controller::Type()
    {
        return L"Windows.Xbox.Input.Controller";
    }
    winrt::Windows::Xbox::System::User Controller::User()
    {
        LOG_INFO_W(L"Controller || User Queried!\n");
        return System::implementation::User::Users().GetAt(Id());
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Xbox::System::IAudioDeviceInfo> Controller::AudioDevices()
    {
        LOG_WARNING("[AudioDevices] STUBBED\n");
        LOG_NOT_IMPLEMENTED(); return {};
    }
    winrt::Windows::Xbox::Input::GameControllerVersionInfo Controller::FirmwareVersionInfo()
    {
        GameControllerVersionInfo controller;
        controller.Minor = 0;
        controller.Major = 0;
        controller.Build = 0;
        controller.Revision = 0;
        return controller;
    }
    winrt::Windows::Xbox::Input::GameControllerVersionInfo Controller::HardwareVersionInfo()
    {
        GameControllerVersionInfo controller;
        controller.Minor = 0;
        controller.Major = 0;
        controller.Build = 0;
        controller.Revision = 0;
        return controller;
    }
    uint16_t Controller::HardwareProductId()
    {
        LOG_NOT_IMPLEMENTED(); return 0;
    }
    uint16_t Controller::HardwareVendorId()
    {
        LOG_NOT_IMPLEMENTED(); return 0;
    }
}