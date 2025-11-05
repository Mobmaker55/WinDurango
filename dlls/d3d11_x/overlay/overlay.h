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
#pragma once
#include <d3d11.h>
#include <dxgi1_2.h>
#include <imgui.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Foundation.h>

namespace wd
{
	class Overlay
	{
	public:
		Overlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, IDXGISwapChain1* pSwapchain);
		~Overlay();
		void Initialize();
		void Shutdown();
		void EnableKeyboard();
		void UpdateXInput();
		void Present();

		void RenderKeyboardWindow();

		void RenderKeyboardRow(const char** keys, int start, int end, bool isUppercase);

		void AddKeyToBuffer(char c);

		void HandleKeyboardSpecialKeys();

	private:
		bool m_bOpen = false;
		bool m_bKeyboard = false;

		ID3D11Device* m_pDevice = nullptr;
		ID3D11DeviceContext* m_pContext = nullptr;
		IDXGISwapChain1* m_pSwapchain = nullptr;
		ID3D11RenderTargetView* m_pRenderTargetView;
	};

	inline Overlay* g_Overlay = nullptr;
	inline HANDLE g_KeyboardFinished;
	inline char g_KeyboardText[ 256 ];
}
