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
#include "dxgi_device.h"

namespace wdi
{
	D3DINTERFACE(IDXGISwapChain, 310d36a0, d2e7, 4c0a, aa, 04, 6a, 9d, 23, b8, 88, 6a) : public IDXGIDeviceSubObject {
	public:
		virtual HRESULT STDMETHODCALLTYPE Present(
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT Flags) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetBuffer(
            /* [in] */ UINT Buffer,
            /* [annotation][in] */
            _In_  REFIID riid,
            /* [annotation][out][in] */
            _COM_Outptr_  void** ppSurface) = 0;

        virtual HRESULT STDMETHODCALLTYPE SetFullscreenState(
            /* [in] */ BOOL Fullscreen,
            /* [annotation][in] */
            _In_opt_  IDXGIOutput* pTarget) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetFullscreenState(
            /* [annotation][out] */
            _Out_opt_  BOOL* pFullscreen,
            /* [annotation][out] */
            _COM_Outptr_opt_result_maybenull_  IDXGIOutput** ppTarget) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetDesc(
            /* [annotation][out] */
            _Out_  DXGI_SWAP_CHAIN_DESC* pDesc) = 0;

        virtual HRESULT STDMETHODCALLTYPE ResizeBuffers(
            /* [in] */ UINT BufferCount,
            /* [in] */ UINT Width,
            /* [in] */ UINT Height,
            /* [in] */ DXGI_FORMAT NewFormat,
            /* [in] */ UINT SwapChainFlags) = 0;

        virtual HRESULT STDMETHODCALLTYPE ResizeTarget(
            /* [annotation][in] */
            _In_  const DXGI_MODE_DESC* pNewTargetParameters) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetContainingOutput(
            /* [annotation][out] */
            _COM_Outptr_  IDXGIOutput** ppOutput) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics(
            /* [annotation][out] */
            _Out_  DXGI_FRAME_STATISTICS* pStats) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount(
            /* [annotation][out] */
            _Out_  UINT* pLastPresentCount) = 0;
	};

    D3DINTERFACE(IDXGISwapChain1, 790a45f7, 0d42, 4876, 98, 3a, 0a, 55, cf, e6, f4, aa) : public IDXGISwapChain {
	public:
    	virtual HRESULT STDMETHODCALLTYPE GetDesc1(
            /* [annotation][out] */
            _Out_  DXGI_SWAP_CHAIN_DESC1* pDesc) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetFullscreenDesc(
            /* [annotation][out] */
            _Out_  DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDesc) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetHwnd(
            /* [annotation][out] */
            _Out_  HWND* pHwnd) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetCoreWindow(
            /* [annotation][in] */
            _In_  REFIID refiid,
            /* [annotation][out] */
            _COM_Outptr_  void** ppUnk) = 0;

        virtual HRESULT STDMETHODCALLTYPE Present1(
            /* [in] */ UINT SyncInterval,
            /* [in] */ UINT PresentFlags,
            /* [annotation][in] */
            _In_  const DXGI_PRESENT_PARAMETERS* pPresentParameters) = 0;

        virtual BOOL STDMETHODCALLTYPE IsTemporaryMonoSupported(void) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetRestrictToOutput(
            /* [annotation][out] */
            _Out_  IDXGIOutput** ppRestrictToOutput) = 0;

        virtual HRESULT STDMETHODCALLTYPE SetBackgroundColor(
            /* [annotation][in] */
            _In_  const DXGI_RGBA* pColor) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetBackgroundColor(
            /* [annotation][out] */
            _Out_  DXGI_RGBA* pColor) = 0;

        virtual HRESULT STDMETHODCALLTYPE SetRotation(
            /* [annotation][in] */
            _In_  DXGI_MODE_ROTATION Rotation) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetRotation(
            /* [annotation][out] */
            _Out_  DXGI_MODE_ROTATION* pRotation) = 0;
    };
}

namespace wd
{
	class dxgi_swapchain : public wdi::IDXGISwapChain1
	{
	public:
		dxgi_swapchain(::IDXGISwapChain1* swapchain) : wrapped_interface(swapchain) { wrapped_interface->AddRef(); }

        IGU_DEFINE_REF

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		HRESULT GetParent(const IID& riid, void** ppParent) override;
		HRESULT GetDevice(const IID& riid, void** ppDevice) override;
		HRESULT Present(UINT SyncInterval, UINT Flags) override;
		HRESULT GetBuffer(UINT Buffer, const IID& riid, void** ppSurface) override;
		HRESULT SetFullscreenState(BOOL Fullscreen, IDXGIOutput* pTarget) override;
		HRESULT GetFullscreenState(BOOL* pFullscreen, IDXGIOutput** ppTarget) override;
		HRESULT GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc) override;
		HRESULT ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat,
			UINT SwapChainFlags) override;
		HRESULT ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters) override;
		HRESULT GetContainingOutput(IDXGIOutput** ppOutput) override;
		HRESULT GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) override;
		HRESULT GetLastPresentCount(UINT* pLastPresentCount) override;
		HRESULT GetDesc1(DXGI_SWAP_CHAIN_DESC1* pDesc) override;
		HRESULT GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDesc) override;
		HRESULT GetHwnd(HWND* pHwnd) override;
		HRESULT GetCoreWindow(const IID& refiid, void** ppUnk) override;
		HRESULT Present1(UINT SyncInterval, UINT PresentFlags,
			const DXGI_PRESENT_PARAMETERS* pPresentParameters) override;
		BOOL IsTemporaryMonoSupported() override;
		HRESULT GetRestrictToOutput(IDXGIOutput** ppRestrictToOutput) override;
		HRESULT SetBackgroundColor(const DXGI_RGBA* pColor) override;
		HRESULT GetBackgroundColor(DXGI_RGBA* pColor) override;
		HRESULT SetRotation(DXGI_MODE_ROTATION Rotation) override;
		HRESULT GetRotation(DXGI_MODE_ROTATION* pRotation) override;

		::IDXGISwapChain1* wrapped_interface;
	};
}


