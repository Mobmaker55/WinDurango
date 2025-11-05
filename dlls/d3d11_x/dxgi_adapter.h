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
	D3DINTERFACE(IDXGIAdapter, 2411e7e1, 12ac, 4ccf, bd, 14, 97, 98, e8, 53, 4d, c0) : public wd::dxgi_object {
	public:
		virtual HRESULT STDMETHODCALLTYPE EnumOutputs(UINT Output, IDXGIOutput** ppOutput) PURE;
		virtual HRESULT STDMETHODCALLTYPE GetDesc(DXGI_ADAPTER_DESC* pDesc) PURE;
		virtual HRESULT STDMETHODCALLTYPE CheckInterfaceSupport(REFGUID InterfaceName, LARGE_INTEGER* pUMDVersion) PURE;
	};
}

namespace wd
{
	class dxgi_adapter : public wdi::IDXGIAdapter
	{
	public:
		dxgi_adapter(::IDXGIAdapter* adapter) : wrapped_interface(adapter) { wrapped_interface->AddRef(); }

		IGU_DEFINE_REF

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override
		{
			if (riid == __uuidof(wdi::IDXGIAdapter))
			{
				*ppvObject = this;
				AddRef();
				return S_OK;
			}
\
			if (riid == __uuidof(wdi::IGraphicsUnwrap))
			{
				*ppvObject = wrapped_interface;
				return S_OK;
			}

			TRACE_INTERFACE_NOT_HANDLED("dxgi_adapter");
			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}

		HRESULT GetParent(const IID& riid, void** ppParent) override;
		HRESULT EnumOutputs(UINT Output, IDXGIOutput** ppOutput) override;
		HRESULT GetDesc(DXGI_ADAPTER_DESC* pDesc) override;
		HRESULT CheckInterfaceSupport(const GUID& InterfaceName, LARGE_INTEGER* pUMDVersion) override;
		::IDXGIAdapter* wrapped_interface;
	};
}
