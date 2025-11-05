#pragma once
#include "Windows.Xbox.Media.GameTransportControlsPropertyChangedEventArgs.g.h"

namespace winrt::Windows::Xbox::Media::implementation
{
    struct GameTransportControlsPropertyChangedEventArgs :
        GameTransportControlsPropertyChangedEventArgsT<GameTransportControlsPropertyChangedEventArgs>
    {
        GameTransportControlsPropertyChangedEventArgs(winrt::Windows::Xbox::Media::GameTransportControlsProperty property)
            : m_property(property) {
        }

        winrt::Windows::Xbox::Media::GameTransportControlsProperty Property();

    private:
        winrt::Windows::Xbox::Media::GameTransportControlsProperty m_property{};
    };
}
