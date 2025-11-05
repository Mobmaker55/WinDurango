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
	D3DINTERFACE(IDXGIDevice, 54ec77fa, 1377, 44e6, 8c, 32, 88, fd, 5f, 44, c8, 4c) : public wd::dxgi_object {
	public:
		virtual HRESULT STDMETHODCALLTYPE GetAdapter(IDXGIAdapter** pAdapter) PURE;
        virtual HRESULT STDMETHODCALLTYPE CreateSurface(const DXGI_SURFACE_DESC* pDesc, UINT NumSurfaces, DXGI_USAGE Usage,
            const DXGI_SHARED_RESOURCE* pSharedResource,
            _Out_writes_(NumSurfaces)  IDXGISurface** ppSurface) PURE;
        virtual HRESULT STDMETHODCALLTYPE QueryResourceResidency(
            _In_reads_(NumResources)  IGraphicsUnknown** ppResources,
            _Out_writes_(NumResources)  DXGI_RESIDENCY* pResidencyStatus,
            /* [in] */ UINT NumResources) PURE;
        virtual HRESULT STDMETHODCALLTYPE SetGPUThreadPriority(
            /* [in] */ INT Priority) PURE;
        virtual HRESULT STDMETHODCALLTYPE GetGPUThreadPriority(
            _Out_  INT* pPriority) PURE;
	};

	D3DINTERFACE(IDXGIDeviceSubObject, 3d3e0379, f9de, 4d58, bb, 6c, 18, d6, 29, 92, f1, a6) : public wd::dxgi_object
	{
		virtual HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void** ppDevice) = 0;
	};
}

namespace wd
{
	class dxgi_device : public wdi::IDXGIDevice
	{
	public:
		dxgi_device(::IDXGIDevice* device) : wrapped_interface(device) { wrapped_interface->AddRef(); }

		IGU_DEFINE_REF

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override
		{
			if (riid == __uuidof(wdi::IDXGIDevice))
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

			TRACE_INTERFACE_NOT_HANDLED("dxgi_device");
			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}

		HRESULT GetParent(const IID& riid, void** ppParent) override;
		HRESULT SetPrivateData(const GUID& Name, UINT DataSize, const void* pData) override;
		HRESULT GetAdapter(wdi::IDXGIAdapter** pAdapter) override;
		HRESULT CreateSurface(const DXGI_SURFACE_DESC* pDesc, UINT NumSurfaces, DXGI_USAGE Usage,
			const DXGI_SHARED_RESOURCE* pSharedResource, IDXGISurface** ppSurface) override;
		HRESULT QueryResourceResidency(IGraphicsUnknown** ppResources, DXGI_RESIDENCY* pResidencyStatus,
			UINT NumResources) override;
		HRESULT SetGPUThreadPriority(INT Priority) override;
		HRESULT GetGPUThreadPriority(INT* pPriority) override;

		::IDXGIDevice* wrapped_interface;
	};
}


