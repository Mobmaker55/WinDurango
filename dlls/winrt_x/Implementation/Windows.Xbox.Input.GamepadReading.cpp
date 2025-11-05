#include "pch.h"
#include "Windows.Xbox.Input.GamepadReading.h"
#include "Windows.Xbox.Input.GamepadReading.g.cpp"

namespace winrt::Windows::Xbox::Input::implementation
{
    winrt::Windows::Foundation::DateTime GamepadReading::Timestamp()
    {
		return winrt::Windows::Foundation::DateTime();
    }
    winrt::Windows::Xbox::Input::GamepadButtons GamepadReading::Buttons()
    {
		return m_Reading.Buttons;
    }
    bool GamepadReading::IsDPadUpPressed()
    {
       return  (int)m_Reading.Buttons & (int)GamepadButtons::DPadUp;
    }
    bool GamepadReading::IsDPadDownPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::DPadDown;
    }
    bool GamepadReading::IsDPadLeftPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::DPadLeft;
    }
    bool GamepadReading::IsDPadRightPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::DPadRight;
    }
    bool GamepadReading::IsMenuPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::Menu;
    }
    bool GamepadReading::IsViewPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::View;
    }
    bool GamepadReading::IsLeftThumbstickPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::LeftThumbstick;
    }
    bool GamepadReading::IsRightThumbstickPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::RightThumbstick;
    }
    bool GamepadReading::IsLeftShoulderPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::LeftShoulder;
    }
    bool GamepadReading::IsRightShoulderPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::RightShoulder;
    }
    bool GamepadReading::IsAPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::A;
    }
    bool GamepadReading::IsBPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::B;
    }
    bool GamepadReading::IsXPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::X;
    }
    bool GamepadReading::IsYPressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::Y;
    }
    float GamepadReading::LeftTrigger()
    {
		return m_Reading.LeftTrigger;
    }
    float GamepadReading::RightTrigger()
    {
		return m_Reading.RightTrigger;
    }
    float GamepadReading::LeftThumbstickX()
    {
		return m_Reading.LeftThumbstickX;
    }
    float GamepadReading::LeftThumbstickY()
    {
		return m_Reading.LeftThumbstickY;
    }
    float GamepadReading::RightThumbstickX()
    {
		return m_Reading.RightThumbstickX;
    }
    float GamepadReading::RightThumbstickY()
    {
		return m_Reading.RightThumbstickY;
    }
    bool GamepadReading::IsPaddle1Pressed()
    {
		return (int)m_Reading.Buttons & (int)GamepadButtons::Paddle1;
    }
    bool GamepadReading::IsPaddle2Pressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::Paddle2;
    }
    bool GamepadReading::IsPaddle3Pressed()
    {
		return (int) m_Reading.Buttons & (int) GamepadButtons::Paddle3;
    }
    bool GamepadReading::IsPaddle4Pressed()
    {
		return  (int) m_Reading.Buttons & (int) GamepadButtons::Paddle4;
    }
}
