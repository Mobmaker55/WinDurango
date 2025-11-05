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
#include "dxgi_object.hpp"

namespace wdi
{
	class IDXGIAdapter;
	D3DINTERFACE(IDXGIFactory, 7b7166ec, 21c7, 44ae, b2, 1a, c9, ae, 32, 1a, e3, 69) : public wd::dxgi_object
	{
	public:
		IDXGIAdapter2 * m_pAdapter;

		virtual HRESULT STDMETHODCALLTYPE EnumAdapters(
			UINT Adapter,
			IDXGIAdapter** ppAdapter) PURE;

		virtual HRESULT STDMETHODCALLTYPE MakeWindowAssociation(
			HWND WindowHandle,
			UINT Flags) PURE;

		virtual HRESULT STDMETHODCALLTYPE GetWindowAssociation(
			HWND* pWindowHandle) PURE;

		virtual HRESULT STDMETHODCALLTYPE CreateSwapChain(
			IGraphicsUnknown* pDevice,
			DXGI_SWAP_CHAIN_DESC* pDesc,
			IDXGISwapChain** ppSwapChain) PURE;

		virtual HRESULT STDMETHODCALLTYPE CreateSoftwareAdapter(
			HMODULE Module,
			IDXGIAdapter** ppAdapter) PURE;
	};

	D3DINTERFACE(IDXGIFactory1, 770aae78, f26f, 4dba, a8, 29, 25, 3c, 83, d1, b3, 87) : public IDXGIFactory
	{
	public:
		virtual HRESULT STDMETHODCALLTYPE EnumAdapters1(
			UINT Adapter,
			IDXGIAdapter1** ppAdapter) PURE;

		virtual BOOL STDMETHODCALLTYPE IsCurrent() PURE;
	};

	D3DINTERFACE(IDXGIFactory2, 50c83a1c, e072, 4c48, 87, b0, 36, 30, fa, 36, a6, d0) : public IDXGIFactory1
	{
	public:
		virtual BOOL STDMETHODCALLTYPE IsWindowedStereoEnabled(void) PURE;

        virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForHwnd(IGraphicsUnknown* pDevice,
            HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc,
            const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc,
            IDXGIOutput* pRestrictToOutput,
            IDXGISwapChain1** ppSwapChain) PURE;

        virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForCoreWindow(
           IGraphicsUnknown* pDevice,
           IUnknown* pWindow,
           DXGI_SWAP_CHAIN_DESC1* pDesc,
           IDXGIOutput* pRestrictToOutput,
           IDXGISwapChain1** ppSwapChain) PURE;

        virtual HRESULT STDMETHODCALLTYPE GetSharedResourceAdapterLuid(
            HANDLE hResource,
            LUID* pLuid) PURE;

        virtual HRESULT STDMETHODCALLTYPE RegisterStereoStatusWindow(
            HWND WindowHandle,
            UINT wMsg,
            DWORD* pdwCookie) PURE;

        virtual HRESULT STDMETHODCALLTYPE RegisterStereoStatusEvent(
            HANDLE hEvent,
            DWORD* pdwCookie) PURE;

        virtual void STDMETHODCALLTYPE UnregisterStereoStatus(
            DWORD dwCookie) PURE;

        virtual HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusWindow(
            HWND WindowHandle,
            UINT wMsg,
            DWORD* pdwCookie) PURE;

        virtual HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusEvent(
            HANDLE hEvent,
            DWORD* pdwCookie) PURE;

        virtual void STDMETHODCALLTYPE UnregisterOcclusionStatus(
            DWORD dwCookie) PURE;

        virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForComposition(
            IGraphicsUnknown* pDevice,
            const DXGI_SWAP_CHAIN_DESC1* pDesc,
            IDXGIOutput* pRestrictToOutput,
            IDXGISwapChain1** ppSwapChain) PURE;
	};
}

namespace wd {
	class dxgi_factory : public wdi::IDXGIFactory2
	{
	public:
        dxgi_factory(::IDXGIFactory2* factory) : wrapped_interface(factory) { wrapped_interface->AddRef(); }

        IGU_DEFINE_REF

        HRESULT QueryInterface(const IID& riid, void** ppvObject) override
        {
			if (riid == __uuidof(wdi::IDXGIFactory) || riid == __uuidof(wdi::IDXGIFactory1) ||
				riid == __uuidof(wdi::IDXGIFactory2))
			{
				*ppvObject = this;
				AddRef();
				return S_OK;
			}

			if (riid == __uuidof(wdi::IGraphicsUnwrap))
			{
				*ppvObject = wrapped_interface;
				return S_OK;
			}

			TRACE_INTERFACE_NOT_HANDLED("dxgi_factory");
			*ppvObject = nullptr;
			return E_NOINTERFACE;
        }

        HRESULT GetParent(const IID& riid, void** ppParent) override;
        HRESULT EnumAdapters1(UINT Adapter, IDXGIAdapter1** ppAdapter) override;
        HRESULT CreateSwapChainForComposition(IGraphicsUnknown* pDevice, const DXGI_SWAP_CHAIN_DESC1* pDesc,
	        IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) override;
        HRESULT CreateSwapChainForHwnd(IGraphicsUnknown* pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc,
	        const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput,
	        IDXGISwapChain1** ppSwapChain) override;
        HRESULT CreateSwapChainForCoreWindow(IGraphicsUnknown* pDevice, IUnknown* pWindow, DXGI_SWAP_CHAIN_DESC1* pDesc,
	        IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) override;
        HRESULT GetSharedResourceAdapterLuid(HANDLE hResource, LUID* pLuid) override;
        HRESULT RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD* pdwCookie) override;
        HRESULT RegisterStereoStatusEvent(HANDLE hEvent, DWORD* pdwCookie) override;
        void UnregisterStereoStatus(DWORD dwCookie) override;
        HRESULT RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD* pdwCookie) override;
        HRESULT RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD* pdwCookie) override;
        void UnregisterOcclusionStatus(DWORD dwCookie) override;
        BOOL IsCurrent() override;
        BOOL IsWindowedStereoEnabled() override;
        HRESULT EnumAdapters(UINT Adapter, wdi::IDXGIAdapter** ppAdapter) override;
        HRESULT MakeWindowAssociation(HWND WindowHandle, UINT Flags) override;
        HRESULT GetWindowAssociation(HWND* pWindowHandle) override;
        HRESULT CreateSwapChain(IGraphicsUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc,
	        IDXGISwapChain** ppSwapChain) override;
        HRESULT CreateSoftwareAdapter(HMODULE Module, wdi::IDXGIAdapter** ppAdapter) override;

private:
        ::IDXGIFactory2* wrapped_interface;
	};
}

