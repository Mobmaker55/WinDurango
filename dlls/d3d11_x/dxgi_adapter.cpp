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
#include "dxgi_adapter.h"
#include "dxgi_factory.h"
#include "../common/Logger.h"

HRESULT wd::dxgi_adapter::GetParent(const IID& riid, void** ppParent)
{
    if (riid == __uuidof(IDXGIFactory) ||
		riid == __uuidof(IDXGIFactory1) ||
		riid == __uuidof(IDXGIFactory2))
    {
        IDXGIFactory2* factory = nullptr;
        HRESULT hr = wrapped_interface->GetParent(IID_PPV_ARGS(&factory));
        *ppParent = new dxgi_factory(factory);
        this->AddRef();
        return hr;
    }

    TRACE_INTERFACE_NOT_HANDLED("dxgi_adapter");
    *ppParent = nullptr;
    return E_NOINTERFACE;
}

HRESULT wd::dxgi_adapter::EnumOutputs(UINT Output, IDXGIOutput** ppOutput)
{
	return wrapped_interface->EnumOutputs(Output, ppOutput);
}

HRESULT wd::dxgi_adapter::GetDesc(DXGI_ADAPTER_DESC* pDesc)
{
	return wrapped_interface->GetDesc(pDesc);
}

HRESULT wd::dxgi_adapter::CheckInterfaceSupport(const GUID& InterfaceName, LARGE_INTEGER* pUMDVersion)
{
	LOG_WARNING("WARN: dxgi_adapter::CheckInterfaceSupport is likely to fail due no support for d3d11.x!!!\n");
	return wrapped_interface->CheckInterfaceSupport(InterfaceName, pUMDVersion);
}
