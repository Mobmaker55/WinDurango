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
#include <cassert>
#include <exception>

#include "d3d11_x.h"
#include "graphics_unknown.h"
#include "../common/Logger.h"

namespace wdi
{
	D3DINTERFACE(ID3D11DeviceChild, 1841e5c8, 16b0, 489b, bc, c8, 44, cf, b0, d5, de, ae) : public wd::graphics_unknown {
		ID3D11Device* m_pDevice;
		void* m_pPrivateData;

		// @Patoke todo: make this access wdi::ID3D11Device instead, this is a temporary fix
		virtual void STDMETHODCALLTYPE GetDevice(::ID3D11Device** ppDevice) = 0;
		virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) = 0;
		virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) = 0;
		virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) = 0;
		virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterfaceGraphics(REFGUID guid, const IGraphicsUnknown* pData) = 0;
		virtual HRESULT STDMETHODCALLTYPE SetName(LPCWSTR pName) = 0;
	};
}

namespace wd
{
	class device_child_x : wdi::ID3D11DeviceChild
	{
	public:
		device_child_x(::ID3D11DeviceChild* device_child) : wrapped_interface(device_child) { wrapped_interface->AddRef(); }

		void STDMETHODCALLTYPE GetDevice(ID3D11Device** ppDevice) override
		{
			LOG_WARNING("WARN: device_child_x::GetDevice returns a PC device!!\n");
			wrapped_interface->GetDevice(ppDevice);
		}

		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) override
		{
			return wrapped_interface->GetPrivateData(guid, pDataSize, pData);
		}

		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) override
		{
			return wrapped_interface->SetPrivateData(guid, DataSize, pData);
		}

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) override
		{
			return wrapped_interface->SetPrivateDataInterface(guid, pData);
		}

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterfaceGraphics(REFGUID guid, const IGraphicsUnknown* pData) override
		{
			TRACE_NOT_IMPLEMENTED("device_child_x");
			return E_NOTIMPL;
		}

	private:
		::ID3D11DeviceChild* wrapped_interface;
	};
}


