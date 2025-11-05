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
#include "device_x.h"
#include <stdexcept>
#include "resource.hpp"
#include "view.hpp"
#include "../common/Logger.h"

HRESULT wd::device_x::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData,
	ID3D11Buffer** ppBuffer)
{
	ID3D11Buffer* buffer = nullptr;
	HRESULT hr = wrapped_interface->CreateBuffer(pDesc, pInitialData, &buffer);

	if (ppBuffer != nullptr)
	{
		*ppBuffer = SUCCEEDED(hr) ? reinterpret_cast<ID3D11Buffer*>(new wd::buffer(buffer)) : nullptr;
	}

	return hr;
}

HRESULT wd::device_x::CreateTexture1D(const D3D11_TEXTURE1D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData,
                                      ID3D11Texture1D** ppTexture1D)
{
	ID3D11Texture1D* texture1d = nullptr;
	HRESULT hr = wrapped_interface->CreateTexture1D(pDesc, pInitialData, &texture1d);

	LOG_INFO("[CreateTexture1D] created texture at 0x%llX\n", texture1d);

	if (ppTexture1D != nullptr)
	{
		*ppTexture1D = SUCCEEDED(hr) ? reinterpret_cast<ID3D11Texture1D*>(new texture_1d(texture1d)) : nullptr;
	}

	return hr;
}

HRESULT wd::device_x::CreateTexture2D(
	const D3D11_TEXTURE2D_DESC* pDesc,
	const D3D11_SUBRESOURCE_DATA* pInitialData,
	ID3D11Texture2D** ppTexture2D)
{
	if (!pDesc || !ppTexture2D)
		return E_INVALIDARG;

	D3D11_TEXTURE2D_DESC fixedDesc = *pDesc;
	fixedDesc.MiscFlags &= ~(D3D11_RESOURCE_MISC_TILE_POOL); // 🚫 Fix the bad flag

	ID3D11Texture2D* texture2d = nullptr;
	HRESULT hr = wrapped_interface->CreateTexture2D(&fixedDesc, pInitialData, &texture2d);

	if (SUCCEEDED(hr) && texture2d)
	{
		// LOG_INFO("[CreateTexture2D] created texture at 0x%p\n", texture2d);
		*ppTexture2D = reinterpret_cast<ID3D11Texture2D*>(new texture_2d(texture2d));
	}
	else
	{
		// LOG_INFO("[CreateTexture2D] failed (HRESULT: 0x%08X)\n", static_cast<unsigned int>(hr));
		*ppTexture2D = nullptr;
	}

	return hr;
}


HRESULT wd::device_x::CreateTexture3D(const D3D11_TEXTURE3D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData,
	ID3D11Texture3D** ppTexture3D)
{
	ID3D11Texture3D* texture3d = nullptr;
	HRESULT hr = wrapped_interface->CreateTexture3D(pDesc, pInitialData, &texture3d);

	LOG_INFO("[CreateTexture3D] created texture at 0x%llX\n", texture3d);

	if (ppTexture3D != nullptr)
	{
		*ppTexture3D = SUCCEEDED(hr) ? reinterpret_cast<ID3D11Texture3D*>(new texture_3d(texture3d)) : nullptr;
	}

	return hr;
}

HRESULT wd::device_x::CreateShaderResourceView(ID3D11Resource* pResource,
											   const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc,
											   ID3D11ShaderResourceView** ppSRView)
{
	// Handle null resource
	if (pResource == nullptr)
	{
		if (ppSRView != nullptr)
			*ppSRView = nullptr;
		return E_INVALIDARG;  // or another appropriate error code
	}

	::ID3D11ShaderResourceView* target = nullptr;
	HRESULT hr = wrapped_interface->CreateShaderResourceView(
		reinterpret_cast<d3d11_resource*>(pResource)->wrapped_interface,
		pDesc,
		&target
	);

	if (ppSRView != nullptr)
	{
		*ppSRView = SUCCEEDED(hr) ? reinterpret_cast<ID3D11ShaderResourceView*>(new shader_resource_view(target))
			: nullptr;
	}
	return hr;
}

HRESULT wd::device_x::CreateUnorderedAccessView(ID3D11Resource* pResource,
                                                const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView)
{
	::ID3D11UnorderedAccessView* target = nullptr;
	HRESULT hr = wrapped_interface->CreateUnorderedAccessView(reinterpret_cast<d3d11_resource*>(pResource)->wrapped_interface, pDesc, &target);

	if (ppUAView != nullptr)
	{
		*ppUAView = SUCCEEDED(hr) ? reinterpret_cast<ID3D11UnorderedAccessView*>(new unordered_access_view(target))
			: nullptr;
	}

	return hr;
}
HRESULT wd::device_x::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
											 ID3D11RenderTargetView** ppRTView)
{
	::ID3D11RenderTargetView* target = nullptr;
	HRESULT hr = wrapped_interface->CreateRenderTargetView(reinterpret_cast<wd::d3d11_resource*>(pResource)->wrapped_interface, pDesc, &target);

	if (ppRTView != nullptr)
	{
		*ppRTView = SUCCEEDED(hr) ? reinterpret_cast<ID3D11RenderTargetView*>(new wd::render_target_view(target))
			: nullptr;
	}

	return hr;
}

HRESULT wd::device_x::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
	ID3D11DepthStencilView** ppDepthStencilView)
{
	::ID3D11DepthStencilView* target = nullptr;
	HRESULT hr = wrapped_interface->CreateDepthStencilView(reinterpret_cast<d3d11_resource*>(pResource)->wrapped_interface, pDesc, &target);

	if (ppDepthStencilView != nullptr)
	{
		*ppDepthStencilView = SUCCEEDED(hr) ? reinterpret_cast<ID3D11DepthStencilView*>(new depth_stencil_view(target))
			: nullptr;
	}

	return hr;
}

HRESULT wd::device_x::CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext** ppDeferredContext)
{
	::ID3D11DeviceContext* ctx{};
	HRESULT hr = wrapped_interface->CreateDeferredContext(ContextFlags, &ctx);

	if (ppDeferredContext != nullptr && SUCCEEDED(hr))
	{
		::ID3D11DeviceContext2* ctx2{};
		ctx->QueryInterface(IID_PPV_ARGS(&ctx2));

		*ppDeferredContext = reinterpret_cast<ID3D11DeviceContext*>(new device_context_x(ctx2));
	}

	return hr;
}

void wd::device_x::GetImmediateContext(ID3D11DeviceContext** ppImmediateContext)
{
	::ID3D11DeviceContext* ctx{};
	wrapped_interface->GetImmediateContext(&ctx);

	if (!ctx) return;

	::ID3D11DeviceContext2* ctx2{};
	ctx->QueryInterface(IID_PPV_ARGS(&ctx2));

	*ppImmediateContext = reinterpret_cast<ID3D11DeviceContext*>(new device_context_x(ctx2));
}

HRESULT wd::device_x::CreateDeferredContext1(UINT ContextFlags, ID3D11DeviceContext1** ppDeferredContext)
{
	LOG_NOT_IMPLEMENTED();
	return wrapped_interface->CreateDeferredContext1(ContextFlags, ppDeferredContext);
}

HRESULT wd::device_x::CreateDeferredContext2(UINT ContextFlags, ID3D11DeviceContext2** ppDeferredContext)
{
	LOG_NOT_IMPLEMENTED();
	return wrapped_interface->CreateDeferredContext2(ContextFlags, ppDeferredContext);
}

void wd::device_x::GetImmediateContextX(wdi::ID3D11DeviceContextX** ppImmediateContextX)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreateCounterSet(const wdi::D3D11X_COUNTER_SET_DESC* pCounterSetDesc,
								   wdi::ID3D11CounterSetX** ppCounterSet)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreateCounterSample(wdi::ID3D11CounterSampleX** ppCounterSample)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::SetDriverHint(UINT Feature, UINT Value)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreateDmaEngineContext(const wdi::D3D11_DMA_ENGINE_CONTEXT_DESC* pDmaEngineContextDesc,
										 wdi::ID3D11DmaEngineContextX** ppDmaDeviceContext)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

BOOL wd::device_x::IsFencePending(UINT64 Fence)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

BOOL wd::device_x::IsResourcePending(ID3D11Resource* pResource)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreatePlacementBuffer(const D3D11_BUFFER_DESC* pDesc, void* pVirtualAddress,
										ID3D11Buffer** ppBuffer)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreatePlacementTexture1D(const D3D11_TEXTURE1D_DESC* pDesc, UINT TileModeIndex, UINT Pitch,
										   void* pVirtualAddress, ID3D11Texture1D** ppTexture1D)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreatePlacementTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, UINT TileModeIndex, UINT Pitch,
										   void* pVirtualAddress, ID3D11Texture2D** ppTexture2D)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreatePlacementTexture3D(const D3D11_TEXTURE3D_DESC* pDesc, UINT TileModeIndex, UINT Pitch,
										   void* pVirtualAddress, ID3D11Texture3D** ppTexture3D)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_x::GetTimestamps(UINT64* pGpuTimestamp, UINT64* pCpuRdtscTimestamp)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreateSamplerStateX(const wdi::D3D11X_SAMPLER_DESC* pSamplerDesc,
									  ID3D11SamplerState** ppSamplerState)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreateDeferredContextX(UINT Flags, wdi::ID3D11DeviceContextX** ppDeferredContext)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_x::GarbageCollect(UINT Flags)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreateDepthStencilStateX(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilStateDesc,
										   ID3D11DepthStencilState** ppDepthStencilState)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreatePlacementRenderableTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, UINT TileModeIndex,
													 UINT Pitch,
													 const wdi::D3D11X_RENDERABLE_TEXTURE_ADDRESSES* pAddresses,
													 ID3D11Texture2D** ppTexture2D)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_x::GetDriverStatistics(UINT StructSize, wdi::D3D11X_DRIVER_STATISTICS* pStatistics)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::CreateComputeContextX(const wdi::D3D11_COMPUTE_CONTEXT_DESC* pComputeContextDesc,
										wdi::ID3D11ComputeContextX** ppComputeContext)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_x::ComposeShaderResourceView(const wdi::D3D11X_DESCRIPTOR_RESOURCE* pDescriptorResource,
										 const wdi::D3D11X_RESOURCE_VIEW_DESC* pViewDesc,
										 wdi::D3D11X_DESCRIPTOR_SHADER_RESOURCE_VIEW* pDescriptorSrv)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_x::ComposeUnorderedAccessView(const wdi::D3D11X_DESCRIPTOR_RESOURCE* pDescriptorResource,
										  const wdi::D3D11X_RESOURCE_VIEW_DESC* pViewDesc,
										  wdi::D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW* pDescriptorUav)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_x::ComposeConstantBufferView(const wdi::D3D11X_DESCRIPTOR_RESOURCE* pDescriptorResource,
										 const wdi::D3D11X_RESOURCE_VIEW_DESC* pViewDesc,
										 wdi::D3D11X_DESCRIPTOR_CONSTANT_BUFFER_VIEW* pDescriptorCb)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_x::ComposeVertexBufferView(const wdi::D3D11X_DESCRIPTOR_RESOURCE* pDescriptorResource,
									   const wdi::D3D11X_RESOURCE_VIEW_DESC* pViewDesc,
									   wdi::D3D11X_DESCRIPTOR_VERTEX_BUFFER_VIEW* pDescriptorVb)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_x::ComposeSamplerState(const wdi::D3D11X_SAMPLER_STATE_DESC* pSamplerDesc,
								   wdi::D3D11X_DESCRIPTOR_SAMPLER_STATE* pDescriptorSamplerState)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_x::PlaceSwapChainView(ID3D11Resource* pSwapChainBuffer, ID3D11View* pView)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_x::SetDebugFlags(UINT Flags)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

UINT wd::device_x::GetDebugFlags()
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}
wdi::D3D11XHANGBEGINCALLBACK m_HangBeginCallback = nullptr;
wdi::D3D11XHANGPRINTCALLBACK m_HangPrintCallback = nullptr;
wdi::D3D11XHANGDUMPCALLBACK  m_HangDumpCallback = nullptr;
void wd::device_x::SetHangCallbacks(
	wdi::D3D11XHANGBEGINCALLBACK pBeginCallback,
	wdi::D3D11XHANGPRINTCALLBACK pPrintCallback,
	wdi::D3D11XHANGDUMPCALLBACK pDumpCallback)
{
	m_HangBeginCallback = pBeginCallback;
	m_HangPrintCallback = pPrintCallback;
	m_HangDumpCallback = pDumpCallback;

	LOG_INFO("SetHangCallbacks called: BeginCallback=%p, PrintCallback=%p, DumpCallback=%p",
			 pBeginCallback, pPrintCallback, pDumpCallback);

	// No-op on PC, but you may simulate hang behavior in testing by manually calling these.
}

void wd::device_x::ReportGpuHang(UINT Flags)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_x::SetGpuMemoryPriority(UINT Priority)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_x::GetGpuHardwareConfiguration(wdi::D3D11X_GPU_HARDWARE_CONFIGURATION* pGpuHardwareConfiguration)
{
	if (!pGpuHardwareConfiguration)
		return;

	// TODO: Replace these constants with dynamic queries if available
	pGpuHardwareConfiguration->GpuFrequency = 853'000'000; // 853 MHz (Xbox One)
	pGpuHardwareConfiguration->HardwareVersion = wdi::D3D11X_HARDWARE_VERSION_XBOX_ONE;
	pGpuHardwareConfiguration->GpuCuCount = 12; // 12 Compute Units (Xbox One baseline)
}

