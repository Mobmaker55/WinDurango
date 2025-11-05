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
#include "dxgi_factory.h"
#include <windows.ui.core.h>
#include <wrl/client.h>
#include <wrl/wrappers/corewrappers.h>

#include "dxgi_swapchain.h"
#include "../kernelx/CoreWindowWrapperX.h"
#include "overlay/overlay.h"
#include <d3d11_2.h>
#include "../common/Logger.h"

#define DXGI_SWAPCHAIN_FLAG_MASK DXGI_SWAP_CHAIN_FLAG_NONPREROTATED | DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE \
		| DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT | DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER | DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY | DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT \
		| DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER | DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO | DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO \
		| DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING \
		| DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS 

HRESULT wd::dxgi_factory::GetParent(const IID& riid, void** ppParent)
{
	return wrapped_interface->GetParent(riid, ppParent);
}

HRESULT wd::dxgi_factory::EnumAdapters1(UINT Adapter, IDXGIAdapter1** ppAdapter)
{
	return wrapped_interface->EnumAdapters1(Adapter, ppAdapter);
}

HRESULT wd::dxgi_factory::CreateSwapChainForComposition(IGraphicsUnknown* pDevice, const DXGI_SWAP_CHAIN_DESC1* pDesc,
	IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain)
{
	return wrapped_interface->CreateSwapChainForComposition(reinterpret_cast<IUnknown*>(pDevice), pDesc, pRestrictToOutput, ppSwapChain);
}

HRESULT wd::dxgi_factory::CreateSwapChainForHwnd(IGraphicsUnknown* pDevice, HWND hWnd,
	const DXGI_SWAP_CHAIN_DESC1* pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc,
	IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain)
{
	return wrapped_interface->CreateSwapChainForHwnd(reinterpret_cast<IUnknown*>(pDevice), hWnd, pDesc, pFullscreenDesc, pRestrictToOutput, ppSwapChain);
}

HRESULT wd::dxgi_factory::CreateSwapChainForCoreWindow(IGraphicsUnknown* pDevice, IUnknown* pWindow,
	DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain)
{
	// Input validation
	if (pDevice == nullptr) {
		LOG_FATAL("CRITICAL: pDevice is null!\n");
		return E_INVALIDARG;
	}
	if (pDesc == nullptr) {
		LOG_FATAL("CRITICAL: pDesc is null!\n");
		return E_INVALIDARG;
	}
	if (ppSwapChain == nullptr) {
		LOG_FATAL("CRITICAL: ppSwapChain is null!\n");
		return E_INVALIDARG;
	}
	if (wrapped_interface == nullptr) {
		LOG_FATAL("CRITICAL: wrapped_interface is null!\n");
		return E_POINTER;
	}

	IDXGISwapChain1* swap = nullptr;
	HRESULT hr;

	pDesc->Flags &= DXGI_SWAPCHAIN_FLAG_MASK;
	pDesc->Scaling = DXGI_SCALING_ASPECT_RATIO_STRETCH;

	::ID3D11Device2* pRealDevice = nullptr;
	hr = pDevice->QueryInterface(__uuidof(wdi::IGraphicsUnwrap), (void**) &pRealDevice);
	if (FAILED(hr)) {
		LOG_FATAL("CRITICAL: dxgi_factory::CreateSwapChainForCoreWindow -> failed to unwrap device, hr=0x%08X\n", hr);
		return hr;
	}

	// Additional null check after QueryInterface
	if (pRealDevice == nullptr) {
		LOG_FATAL("CRITICAL: pRealDevice is null after QueryInterface!\n");
		return E_POINTER;
	}

	if (pWindow == nullptr) {
		Microsoft::WRL::ComPtr<ABI::Windows::UI::Core::ICoreWindowStatic> coreWindowStatic;
		hr = RoGetActivationFactory(Microsoft::WRL::Wrappers::HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), IID_PPV_ARGS(&coreWindowStatic));
		if (FAILED(hr)) {
			LOG_FATAL("CRITICAL: Failed to get CoreWindowStatic factory, hr=0x%08X\n", hr);
			pRealDevice->Release();
			return hr;
		}

		Microsoft::WRL::ComPtr<ABI::Windows::UI::Core::ICoreWindow> coreWindow;
		hr = coreWindowStatic->GetForCurrentThread(&coreWindow);
		if (FAILED(hr) || !coreWindow) {
			LOG_FATAL("CRITICAL: Failed to get CoreWindow for current thread, hr=0x%08X\n", hr);
			pRealDevice->Release();
			return FAILED(hr) ? hr : E_FAIL;
		}

		pWindow = coreWindow.Get();
		hr = wrapped_interface->CreateSwapChainForCoreWindow(pRealDevice, pWindow, pDesc, pRestrictToOutput, &swap);
		if (FAILED(hr)) {
			LOG_FATAL("CRITICAL: CreateSwapChainForCoreWindow failed (null window path), hr=0x%08X\n", hr);
			pRealDevice->Release();
			return hr;
		}

		if (swap == nullptr) {
			LOG_FATAL("CRITICAL: CreateSwapChainForCoreWindow succeeded but swap is null!\n");
			pRealDevice->Release();
			return E_FAIL;
		}

		*ppSwapChain = reinterpret_cast<IDXGISwapChain1*>(new dxgi_swapchain(swap));
	}
	else {
		// Validate the window wrapper
		CoreWindowWrapperX* windowWrapper = reinterpret_cast<CoreWindowWrapperX*>(pWindow);
		if (windowWrapper == nullptr || windowWrapper->m_realWindow == nullptr) {
			LOG_FATAL("CRITICAL: Invalid window wrapper or m_realWindow is null!\n");
			pRealDevice->Release();
			return E_INVALIDARG;
		}

		hr = wrapped_interface->CreateSwapChainForCoreWindow(pRealDevice, windowWrapper->m_realWindow, pDesc, pRestrictToOutput, &swap);
		if (FAILED(hr)) {
			LOG_FATAL("CRITICAL: CreateSwapChainForCoreWindow failed (wrapper window path), hr=0x%08X\n", hr);
			pRealDevice->Release();
			return hr;
		}

		if (swap == nullptr) {
			LOG_FATAL("CRITICAL: CreateSwapChainForCoreWindow succeeded but swap is null!\n");
			pRealDevice->Release();
			return E_FAIL;
		}

		*ppSwapChain = reinterpret_cast<IDXGISwapChain1*>(new dxgi_swapchain(swap));
	}

	// Initialize overlay if needed
	if (wd::g_Overlay == nullptr) {
		::ID3D11DeviceContext* ctx = nullptr;
		pRealDevice->GetImmediateContext(&ctx);
		if (ctx == nullptr) {
			LOG_FATAL("WARNING: Failed to get immediate context for overlay initialization\n");
		}
		else {
			wd::g_Overlay = new wd::Overlay(pRealDevice, ctx, swap);
			if (wd::g_Overlay != nullptr) {
				wd::g_Overlay->Initialize();
			}
		}
	}

	// Clean up the reference we got from QueryInterface
	pRealDevice->Release();

	return hr;
}

HRESULT wd::dxgi_factory::GetSharedResourceAdapterLuid(HANDLE hResource, LUID* pLuid)
{
	return wrapped_interface->GetSharedResourceAdapterLuid(hResource, pLuid);
}

HRESULT wd::dxgi_factory::RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD* pdwCookie)
{
	return wrapped_interface->RegisterStereoStatusWindow(WindowHandle, wMsg, pdwCookie);
}

HRESULT wd::dxgi_factory::RegisterStereoStatusEvent(HANDLE hEvent, DWORD* pdwCookie)
{
	return wrapped_interface->RegisterStereoStatusEvent(hEvent, pdwCookie);
}

void wd::dxgi_factory::UnregisterStereoStatus(DWORD dwCookie)
{
	wrapped_interface->UnregisterStereoStatus(dwCookie);
}

HRESULT wd::dxgi_factory::RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD* pdwCookie)
{
	return wrapped_interface->RegisterOcclusionStatusWindow(WindowHandle, wMsg, pdwCookie);
}

HRESULT wd::dxgi_factory::RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD* pdwCookie)
{
	return wrapped_interface->RegisterOcclusionStatusEvent(hEvent, pdwCookie);
}

void wd::dxgi_factory::UnregisterOcclusionStatus(DWORD dwCookie)
{
	return wrapped_interface->UnregisterOcclusionStatus(dwCookie);
}

BOOL wd::dxgi_factory::IsCurrent()
{
	return wrapped_interface->IsCurrent();
}

BOOL wd::dxgi_factory::IsWindowedStereoEnabled()
{
	return wrapped_interface->IsWindowedStereoEnabled();
}

HRESULT wd::dxgi_factory::EnumAdapters(UINT Adapter, wdi::IDXGIAdapter** ppAdapter)
{
	LOG_WARNING("WARN: dxgi_factory::EnumAdapters does not wrap IDXGIAdapter!!!\n");
	return wrapped_interface->EnumAdapters(Adapter, reinterpret_cast<IDXGIAdapter**>(ppAdapter));
}

HRESULT wd::dxgi_factory::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
{
	return wrapped_interface->MakeWindowAssociation(WindowHandle, Flags);
}

HRESULT wd::dxgi_factory::GetWindowAssociation(HWND* pWindowHandle)
{
	return wrapped_interface->GetWindowAssociation(pWindowHandle);
}

HRESULT wd::dxgi_factory::CreateSwapChain(IGraphicsUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc,
	IDXGISwapChain** ppSwapChain)
{
	return wrapped_interface->CreateSwapChain(reinterpret_cast<IUnknown*>(pDevice), pDesc, ppSwapChain);
}

HRESULT wd::dxgi_factory::CreateSoftwareAdapter(HMODULE Module, wdi::IDXGIAdapter** ppAdapter)
{
	LOG_WARNING("WARN: dxgi_factory::CreateSoftwareAdapter does not wrap IDXGIAdapter!!!\n");
	return wrapped_interface->CreateSoftwareAdapter(Module, reinterpret_cast<IDXGIAdapter**>(ppAdapter));
}
