/*
================================================================================
DISCLAIMER AND LICENSE REQUIREMENT

This code is provided with the condition that if you use, modify, or distribute
this code in your project, you are required to make your project open source
under a license compatible with the GNU General Public License (GPL) or a
similarly strong copyleft license.

By using this code, you agree to:
1. Disclose your complete source code of any project incorporating this code.
2. Include this disclaimer in any copies or substantial portions of this file.
3. Provide clear attribution to the original author.

If you do not agree to these terms, you do not have permission to use this code.

================================================================================
*/
#include "overlay.h"

#include "../../../thirdparty/imgui/imgui.h"
#include "../../../thirdparty/imgui/backends/imgui_impl_dx11.h"
#include "../../../thirdparty/imgui_impl_uwp.h"
#include <Xinput.h>
#include <winrt/windows.graphics.display.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Foundation.h>

using namespace winrt;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
#pragma comment(lib, "xinput.lib")

extern char g_KeyboardText[ 256 ];
extern HANDLE g_KeyboardFinished;

wd::Overlay::Overlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, IDXGISwapChain1* pSwapchain)
    : m_pDevice(pDevice), m_pContext(pContext), m_pSwapchain(pSwapchain), m_pRenderTargetView(nullptr), m_bKeyboard(false)
{
}

wd::Overlay::~Overlay()
{
    Shutdown();
    m_pDevice = nullptr;
    m_pContext = nullptr;
    m_pSwapchain = nullptr;
}
void SetupImGuiKeyboardInputUWP();
ImGuiKey MapVirtualKeyToImGuiKey(winrt::Windows::System::VirtualKey key);

void wd::Overlay::Initialize()
{
    g_KeyboardFinished = CreateEventA(NULL, FALSE, FALSE, "KeyboardFinished");

    ID3D11Texture2D* pBackBuffer = nullptr;
    m_pSwapchain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
    if (pBackBuffer) pBackBuffer->Release();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    ImGui::StyleColorsDark();

    ImGui_ImplUwp_InitForCurrentView();
    ImGui_ImplDX11_Init(m_pDevice, m_pContext);
    SetupImGuiKeyboardInputUWP();
}




void SetupImGuiKeyboardInputUWP()
{
    CoreWindow window = CoreWindow::GetForCurrentThread();

    window.KeyDown(TypedEventHandler<CoreWindow, KeyEventArgs>(
        [](CoreWindow const&, KeyEventArgs const& args)
        {
            ImGuiKey key = MapVirtualKeyToImGuiKey(args.VirtualKey());
            if (key != ImGuiKey_None)
                ImGui::GetIO().AddKeyEvent(key, true);
        }));

    window.KeyUp(TypedEventHandler<CoreWindow, KeyEventArgs>(
        [](CoreWindow const&, KeyEventArgs const& args)
        {
            ImGuiKey key = MapVirtualKeyToImGuiKey(args.VirtualKey());
            if (key != ImGuiKey_None)
                ImGui::GetIO().AddKeyEvent(key, false);
        }));

    window.CharacterReceived(TypedEventHandler<CoreWindow, CharacterReceivedEventArgs>(
        [](CoreWindow const&, CharacterReceivedEventArgs const& args)
        {
            ImGui::GetIO().AddInputCharacter(static_cast<unsigned int>(args.KeyCode()));
        }));
}
ImGuiKey MapVirtualKeyToImGuiKey(VirtualKey key)
{
    switch (key)
    {
    case VirtualKey::Tab: return ImGuiKey_Tab;
    case VirtualKey::Enter: return ImGuiKey_Enter;
    case VirtualKey::Escape: return ImGuiKey_Escape;
    case VirtualKey::Back: return ImGuiKey_Backspace;
    case VirtualKey::Space: return ImGuiKey_Space;
    case VirtualKey::Left: return ImGuiKey_LeftArrow;
    case VirtualKey::Right: return ImGuiKey_RightArrow;
    case VirtualKey::Up: return ImGuiKey_UpArrow;
    case VirtualKey::Down: return ImGuiKey_DownArrow;

    case VirtualKey::A: return ImGuiKey_A;
    case VirtualKey::B: return ImGuiKey_B;
    case VirtualKey::C: return ImGuiKey_C;
    case VirtualKey::D: return ImGuiKey_D;
    case VirtualKey::E: return ImGuiKey_E;
    case VirtualKey::F: return ImGuiKey_F;
    case VirtualKey::G: return ImGuiKey_G;
    case VirtualKey::H: return ImGuiKey_H;
    case VirtualKey::I: return ImGuiKey_I;
    case VirtualKey::J: return ImGuiKey_J;
    case VirtualKey::K: return ImGuiKey_K;
    case VirtualKey::L: return ImGuiKey_L;
    case VirtualKey::M: return ImGuiKey_M;
    case VirtualKey::N: return ImGuiKey_N;
    case VirtualKey::O: return ImGuiKey_O;
    case VirtualKey::P: return ImGuiKey_P;
    case VirtualKey::Q: return ImGuiKey_Q;
    case VirtualKey::R: return ImGuiKey_R;
    case VirtualKey::S: return ImGuiKey_S;
    case VirtualKey::T: return ImGuiKey_T;
    case VirtualKey::U: return ImGuiKey_U;
    case VirtualKey::V: return ImGuiKey_V;
    case VirtualKey::W: return ImGuiKey_W;
    case VirtualKey::X: return ImGuiKey_X;
    case VirtualKey::Y: return ImGuiKey_Y;
    case VirtualKey::Z: return ImGuiKey_Z;

    case VirtualKey::Number0: return ImGuiKey_0;
    case VirtualKey::Number1: return ImGuiKey_1;
    case VirtualKey::Number2: return ImGuiKey_2;
    case VirtualKey::Number3: return ImGuiKey_3;
    case VirtualKey::Number4: return ImGuiKey_4;
    case VirtualKey::Number5: return ImGuiKey_5;
    case VirtualKey::Number6: return ImGuiKey_6;
    case VirtualKey::Number7: return ImGuiKey_7;
    case VirtualKey::Number8: return ImGuiKey_8;
    case VirtualKey::Number9: return ImGuiKey_9;

    default: return ImGuiKey_None;
    }
}

void wd::Overlay::Shutdown()
{
    if (m_pRenderTargetView)
    {
        m_pRenderTargetView->Release();
        m_pRenderTargetView = nullptr;
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplUwp_Shutdown();
    ImGui::DestroyContext();
}

void wd::Overlay::EnableKeyboard()
{
    m_bKeyboard = true;
}

void wd::Overlay::UpdateXInput()
{
    XINPUT_STATE state = {};
    if (XInputGetState(0, &state) == ERROR_SUCCESS)
    {
        ImGuiIO& io = ImGui::GetIO();

#define GAMEPAD_KEY(key, condition) io.AddKeyEvent(ImGuiKey_##key, (condition))

        // Digital buttons
        GAMEPAD_KEY(GamepadDpadUp, state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
        GAMEPAD_KEY(GamepadDpadDown, state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
        GAMEPAD_KEY(GamepadDpadLeft, state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
        GAMEPAD_KEY(GamepadDpadRight, state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
        GAMEPAD_KEY(GamepadFaceDown, state.Gamepad.wButtons & XINPUT_GAMEPAD_A);      // Accept
        GAMEPAD_KEY(GamepadFaceRight, state.Gamepad.wButtons & XINPUT_GAMEPAD_B);      // Cancel
        GAMEPAD_KEY(GamepadStart, state.Gamepad.wButtons & XINPUT_GAMEPAD_START);
        GAMEPAD_KEY(GamepadBack, state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);

#undef GAMEPAD_KEY

        // Left analog stick as analog navigation
        const float deadzone = static_cast<float>(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
        const float maxValue = 32767.0f;

        float lx = static_cast<float>(state.Gamepad.sThumbLX);
        float ly = static_cast<float>(state.Gamepad.sThumbLY);

        float normX = 0.0f;
        float normY = 0.0f;

        if (fabsf(lx) > deadzone)
            normX = (fabsf(lx) - deadzone) / (maxValue - deadzone) * (lx > 0 ? 1.0f : -1.0f);
        if (fabsf(ly) > deadzone)
            normY = (fabsf(ly) - deadzone) / (maxValue - deadzone) * (ly > 0 ? 1.0f : -1.0f);

        normX = std::clamp(normX, -1.0f, 1.0f);
        normY = std::clamp(normY, -1.0f, 1.0f);

        io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickLeft, normX < 0.0f, -normX);
        io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickRight, normX > 0.0f, normX);
        io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickUp, normY > 0.0f, normY); // Y+ is up
        io.AddKeyAnalogEvent(ImGuiKey_GamepadLStickDown, normY < 0.0f, -normY);
    }
}


void wd::Overlay::Present()
{
    UpdateXInput();
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplUwp_NewFrame();
    ImGui::NewFrame();

    if (m_bKeyboard)
        RenderKeyboardWindow();

    ImGui::Render();
    m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void wd::Overlay::RenderKeyboardWindow()
{
    static bool isUppercase = false;
    static bool isSymbols = false;

    const char* keys[] = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'",
        "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/"
    };

    const char* symbols[] = {
        "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+",
        "~", "`", "|", "\\", "{", "}", "[", "]", ":", ";", "\"", "'",
        "<", ">", "?", "/", ",", ".", "=", "-"
    };

    const char** currentKeys = isSymbols ? symbols : keys;

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(500, 330));
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::Begin("WinDurango Keyboard", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);

    ImGui::InputText(" ", g_KeyboardText, IM_ARRAYSIZE(g_KeyboardText));

    if (ImGui::Button(isUppercase ? "Lowercase" : "Uppercase"))
        isUppercase = !isUppercase;
    ImGui::SameLine();
    if (ImGui::Button(isSymbols ? "Letters" : "Symbols"))
        isSymbols = !isSymbols;

    ImGui::NewLine();
    RenderKeyboardRow(currentKeys, 0, 12, isUppercase);
    RenderKeyboardRow(currentKeys, 12, 24, isUppercase);
    if (!isSymbols) RenderKeyboardRow(currentKeys, 24, 35, isUppercase);
    else            RenderKeyboardRow(currentKeys, 24, 32, isUppercase);
    if (!isSymbols) RenderKeyboardRow(currentKeys, 35, 44, isUppercase);

    ImGui::NewLine();
    HandleKeyboardSpecialKeys();

    ImGui::End();
}

void wd::Overlay::RenderKeyboardRow(const char** keys, int start, int end, bool isUppercase)
{
    ImVec2 buttonSize(30, 30);
    for (int i = start; i < end; ++i)
    {
        ImGui::PushID(i);
        if (ImGui::Button(keys[ i ], buttonSize))
            AddKeyToBuffer(isUppercase ? keys[ i ][ 0 ] : tolower(keys[ i ][ 0 ]));
        ImGui::PopID();
        ImGui::SameLine();
    }
    ImGui::NewLine();
}

void wd::Overlay::AddKeyToBuffer(char c)
{
    size_t len = strlen(g_KeyboardText);
    if (len < 255)
    {
        g_KeyboardText[ len ] = c;
        g_KeyboardText[ len + 1 ] = '\0';
    }
}

void wd::Overlay::HandleKeyboardSpecialKeys()
{
    ImVec2 buttonSize(30, 30);

    if (ImGui::Button("Space", ImVec2(60, 30)) || ImGui::IsKeyPressed(ImGuiKey_Space) || ImGui::IsKeyPressed(ImGuiKey_GamepadFaceUp))
        AddKeyToBuffer(' ');
    ImGui::SameLine();

    if (ImGui::Button("Backspace", ImVec2(90, 30)) ||
        ImGui::IsKeyPressed(ImGuiKey_Backspace) ||
        ImGui::IsKeyPressed(ImGuiKey_GamepadFaceLeft))
    {
        size_t len = strlen(g_KeyboardText);
        if (len > 0)
            g_KeyboardText[ len - 1 ] = '\0';
    }
    ImGui::SameLine();

    if (ImGui::Button("OK", buttonSize) ||
        ImGui::IsKeyPressed(ImGuiKey_Enter) ||
        ImGui::IsKeyPressed(ImGuiKey_GamepadStart))
    {
        m_bKeyboard = false;
        SetEvent(g_KeyboardFinished);
    }
}
