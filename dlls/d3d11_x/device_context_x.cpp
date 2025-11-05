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
#include <d3d11_1.h>
#include <d3d11_2.h>
#include "device_context_x.h"
#include <stdexcept>
#include "view.hpp"
#include <d3d11.h>
#include <cassert>
#include <cstdio>
#include "../common/Logger.h"

void wd::device_context_x::GetDevice(ID3D11Device** ppDevice)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::GetPrivateData(const GUID& guid, UINT* pDataSize, void* pData)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::SetPrivateData(const GUID& guid, UINT DataSize, const void* pData)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::SetPrivateDataInterface(const GUID& guid, const IUnknown* pData)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::SetPrivateDataInterfaceGraphics(const GUID& guid, const IGraphicsUnknown* pData)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::SetName(LPCWSTR pName)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	if (ppConstantBuffers != nullptr && *ppConstantBuffers != nullptr)
	{
		ID3D11Buffer* modifiedBuffers[ D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT ];
		for (UINT i = 0; i < NumBuffers; ++i)
		{
			modifiedBuffers[ i ] = reinterpret_cast<wd::buffer*>(ppConstantBuffers[ i ])->wrapped_interface;
		}
		wrapped_interface->VSSetConstantBuffers(StartSlot, NumBuffers, modifiedBuffers);
	}
	else
	{
		wrapped_interface->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
	}
}

void wd::device_context_x::Draw(UINT VertexCount, UINT StartVertexLocation)
{
	ProcessDirtyFlags();
	wrapped_interface->Draw(VertexCount, StartVertexLocation);
}

HRESULT wd::device_context_x::Map(ID3D11Resource* pResource, UINT Subresource,
								  D3D11_MAP MapType, UINT MapFlags,
								  D3D11_MAPPED_SUBRESOURCE* pMappedResource)
{
	// Handle null resource
	if (pResource == nullptr)
	{
		if (pMappedResource != nullptr)
		{
			// Clear the output structure
			ZeroMemory(pMappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
		}
		return E_INVALIDARG;
	}

	return wrapped_interface->Map(
		reinterpret_cast<d3d11_resource*>(pResource)->wrapped_interface,
		Subresource,
		MapType,
		MapFlags,
		pMappedResource
	);
}

void wd::device_context_x::Unmap(ID3D11Resource* pResource, UINT Subresource)
{
	wrapped_interface->Unmap(reinterpret_cast<d3d11_resource*>(pResource)->wrapped_interface, Subresource);
}

void wd::device_context_x::PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	ID3D11Buffer* buffers[ D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT ] = {};

	for (UINT i = 0; i < NumBuffers; ++i)
	{
		if (ppConstantBuffers && ppConstantBuffers[ i ])
		{
			wdi::ID3D11Buffer* wdi_buf = nullptr;
			HRESULT hr = ppConstantBuffers[ i ]->QueryInterface(__uuidof(wdi::ID3D11Buffer), reinterpret_cast<void**>(&wdi_buf));
			if (SUCCEEDED(hr) && wdi_buf != nullptr)
			{
				auto wrapped = static_cast<wd::buffer*>(wdi_buf);
				buffers[ i ] = wrapped->wrapped_interface;
				wdi_buf->Release();
			}
			else
			{
				buffers[ i ] = ppConstantBuffers[ i ]; // passthrough if not wrapped
			}
		}
		else
		{
			buffers[ i ] = nullptr;
		}
	}

	wrapped_interface->PSSetConstantBuffers(StartSlot, NumBuffers, buffers);
}



void wd::device_context_x::IASetInputLayout(ID3D11InputLayout* pInputLayout)
{
	wrapped_interface->IASetInputLayout(pInputLayout);
}

void wd::device_context_x::IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers,
	const UINT* pStrides, const UINT* pOffsets)
{
	if (NumBuffers > D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - StartSlot)
	{
		LOG_WARNING("WARN: device_context_x::IASetVertexBuffers: NumBuffers > D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - StartSlot\n");
		return;
	}

	if (ppVertexBuffers != NULL)
	{
		ID3D11Buffer* modifiedBuffers[ D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT ];
		for (UINT i = 0; i < NumBuffers; i++)
		{
			if (ppVertexBuffers[ i ] == nullptr)
				modifiedBuffers[ i ] = nullptr;
			else
				modifiedBuffers[ i ] = reinterpret_cast<wd::buffer*>(ppVertexBuffers[ i ])->wrapped_interface;
		}

		wrapped_interface->IASetVertexBuffers(StartSlot, NumBuffers, modifiedBuffers, pStrides, pOffsets);
	}
	else
	{
		wrapped_interface->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
	}
}

void wd::device_context_x::GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	::ID3D11Buffer* modifiedBuffers[ D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT ] = {};
	for (UINT i = 0; i < NumBuffers; i++)
	{
		if (ppConstantBuffers[ i ] == nullptr)
			modifiedBuffers[ i ] = 0;
		else
			modifiedBuffers[ i ] = reinterpret_cast<wd::buffer*>(ppConstantBuffers[ i ])->wrapped_interface;
	}

	wrapped_interface->GSSetConstantBuffers(StartSlot, NumBuffers, modifiedBuffers);

}


void wd::device_context_x::GSSetShader(ID3D11GeometryShader* pShader)
{
	wrapped_interface->GSSetShader(pShader, nullptr, 0);
}

void wd::device_context_x::VSSetShaderResources(ID3D11ShaderResourceView* const* ppShaderResourceViews, UINT StartSlot,
	UINT PacketHeader)
{
	UINT NumViews = (PacketHeader >> 19) + 1;

	if (ppShaderResourceViews != NULL)
	{
		ID3D11ShaderResourceView* modifiedViews[ D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT ];

		for (UINT i = 0; i < NumViews; i++)
		{
			if (ppShaderResourceViews[ i ] == nullptr)
				modifiedViews[ i ] = nullptr;
			else
				modifiedViews[ i ] = reinterpret_cast<shader_resource_view*>(ppShaderResourceViews[ i ])->wrapped_interface;
		}
		wrapped_interface->VSSetShaderResources(StartSlot, NumViews, modifiedViews);
	}
	else {
		wrapped_interface->VSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}

void wd::device_context_x::GSSetShaderResources(ID3D11ShaderResourceView* const* ppShaderResourceViews, UINT StartSlot,
	UINT PacketHeader)
{
	UINT NumViews = (PacketHeader >> 19) + 1;

	if (ppShaderResourceViews != NULL)
	{
		ID3D11ShaderResourceView* modifiedViews[ D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT ];

		for (UINT i = 0; i < NumViews; i++)
		{
			if (ppShaderResourceViews[ i ] == nullptr)
				modifiedViews[ i ] = nullptr;
			else
				modifiedViews[ i ] = reinterpret_cast<shader_resource_view*>(ppShaderResourceViews[ i ])->wrapped_interface;
		}
		wrapped_interface->GSSetShaderResources(StartSlot, NumViews, modifiedViews);
	}
	else
	{
		wrapped_interface->GSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}

void wd::device_context_x::DrawAuto()
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::HSSetShaderResources(ID3D11ShaderResourceView* const* ppShaderResourceViews, UINT StartSlot,
	UINT PacketHeader)
{
	UINT NumViews = (PacketHeader >> 19) + 1;

	if (ppShaderResourceViews != NULL)
	{
		ID3D11ShaderResourceView* modifiedViews[ D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT ];

		for (UINT i = 0; i < NumViews; i++)
		{
			if (ppShaderResourceViews[ i ] == nullptr)
				modifiedViews[ i ] = nullptr;
			else
				modifiedViews[ i ] = reinterpret_cast<shader_resource_view*>(ppShaderResourceViews[ i ])->wrapped_interface;
		}
		wrapped_interface->HSSetShaderResources(StartSlot, NumViews, modifiedViews);
	}
	else
	{
		wrapped_interface->HSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}

void wd::device_context_x::HSSetShader(ID3D11HullShader* pHullShader)
{
	wrapped_interface->HSSetShader(pHullShader, nullptr, 0);
}

void wd::device_context_x::DSSetShaderResources(ID3D11ShaderResourceView* const* ppShaderResourceViews, UINT StartSlot,
	UINT PacketHeader)
{
	UINT NumViews = (PacketHeader >> 19) + 1;

	if (ppShaderResourceViews != NULL)
	{
		ID3D11ShaderResourceView* modifiedViews[ D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT ];

		for (UINT i = 0; i < NumViews; i++)
		{
			if (ppShaderResourceViews[ i ] == nullptr)
				modifiedViews[ i ] = nullptr;
			else
				modifiedViews[ i ] = reinterpret_cast<shader_resource_view*>(ppShaderResourceViews[ i ])->wrapped_interface;
		}
		wrapped_interface->DSSetShaderResources(StartSlot, NumViews, modifiedViews);
	}
	else
	{
		wrapped_interface->DSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}

void wd::device_context_x::DSSetShader(ID3D11DomainShader* pDomainShader)
{
	wrapped_interface->DSSetShader(pDomainShader, nullptr, 0);
}

void wd::device_context_x::CSSetShaderResources(ID3D11ShaderResourceView* const* ppShaderResourceViews, UINT StartSlot,
	UINT PacketHeader)
{

	UINT NumViews = (PacketHeader >> 19) + 1;

	if (ppShaderResourceViews != NULL)
	{
		ID3D11ShaderResourceView* modifiedViews[ D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT ];

		for (UINT i = 0; i < NumViews; i++)
		{
			if (ppShaderResourceViews[ i ] == nullptr)
				modifiedViews[ i ] = nullptr;
			else
				modifiedViews[ i ] = reinterpret_cast<shader_resource_view*>(ppShaderResourceViews[ i ])->wrapped_interface;
		}
		wrapped_interface->CSSetShaderResources(StartSlot, NumViews, modifiedViews);
	}
	else
	{
		wrapped_interface->CSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}

void wd::device_context_x::CSSetShader(ID3D11ComputeShader* pComputeShader)
{
	wrapped_interface->CSSetShader(pComputeShader, nullptr, 0);
}

void wd::device_context_x::VSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	wrapped_interface->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::Begin(ID3D11Asynchronous* pAsync)
{
	wrapped_interface->Begin(pAsync);
}

void wd::device_context_x::End(ID3D11Asynchronous* pAsync)
{
	wrapped_interface->End(pAsync);
}

HRESULT wd::device_context_x::GetData(ID3D11Asynchronous* pAsync, void* pData, UINT DataSize, UINT GetDataFlags)
{
	return wrapped_interface->GetData(pAsync, pData, DataSize, GetDataFlags);
}

void wd::device_context_x::SetPredication(ID3D11Predicate* pPredicate, BOOL PredicateValue)
{
	wrapped_interface->SetPredication(pPredicate, PredicateValue);
}

void wd::device_context_x::GSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	wrapped_interface->GSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView* const* ppRenderTargetViews,
	ID3D11DepthStencilView* pDepthStencilView)
{
	auto* depthStencilView = pDepthStencilView;
	if (depthStencilView != nullptr)
		depthStencilView = reinterpret_cast<depth_stencil_view*>(pDepthStencilView)->wrapped_interface;

	if (ppRenderTargetViews != NULL)
	{
		ID3D11RenderTargetView* modifiedViews[ D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT ];
		for (UINT i = 0; i < NumViews; i++)
		{
			if (ppRenderTargetViews[ i ] == nullptr)
				modifiedViews[ i ] = nullptr;
			else
				modifiedViews[ i ] = reinterpret_cast<render_target_view*>(ppRenderTargetViews[ i ])->wrapped_interface;
		}
		wrapped_interface->OMSetRenderTargets(NumViews, modifiedViews, depthStencilView);
	}
	else
	{
		wrapped_interface->OMSetRenderTargets(NumViews, ppRenderTargetViews, depthStencilView);
	}
}

void wd::device_context_x::OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs,
	ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView, UINT UAVStartSlot,
	UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts)
{
	wrapped_interface->OMSetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, pDepthStencilView,
	                                                                UAVStartSlot, NumUAVs, ppUnorderedAccessViews,
	                                                                pUAVInitialCounts);
}

void wd::device_context_x::OMSetBlendState(ID3D11BlendState* pBlendState, const FLOAT BlendFactor[4], UINT SampleMask)
{
	wrapped_interface->OMSetBlendState(pBlendState, BlendFactor, SampleMask);
}

void wd::device_context_x::OMSetDepthStencilState(ID3D11DepthStencilState* pDepthStencilState, UINT StencilRef)
{
	wrapped_interface->OMSetDepthStencilState(pDepthStencilState, StencilRef);
}

void wd::device_context_x::SOSetTargets(UINT NumBuffers, ID3D11Buffer* const* ppSOTargets, const UINT* pOffsets)
{
	wrapped_interface->SOSetTargets(NumBuffers, ppSOTargets, pOffsets);
}

void wd::device_context_x::DrawIndexedInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	wrapped_interface->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void wd::device_context_x::DrawInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	wrapped_interface->DrawInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void wd::device_context_x::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
{
	wrapped_interface->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

void wd::device_context_x::DispatchIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	wrapped_interface->DispatchIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void wd::device_context_x::RSSetState(ID3D11RasterizerState* pRasterizerState)
{
	wrapped_interface->RSSetState(pRasterizerState);
}

void wd::device_context_x::RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT* pViewports)
{
	wrapped_interface->RSSetViewports(NumViewports, pViewports);
}

void wd::device_context_x::RSSetScissorRects(UINT NumRects, const D3D11_RECT* pRects)
{
	wrapped_interface->RSSetScissorRects(NumRects, pRects);
}

void wd::device_context_x::CopySubresourceRegion(ID3D11Resource* pDstResource, UINT DstSubresource, UINT DstX,
	UINT DstY, UINT DstZ, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox)
{
	wrapped_interface->CopySubresourceRegion(reinterpret_cast<d3d11_resource*>(pDstResource)->wrapped_interface, DstSubresource, DstX, DstY, DstZ, reinterpret_cast<d3d11_resource*>(pSrcResource)->wrapped_interface,
	                                            SrcSubresource, pSrcBox);
}

void wd::device_context_x::CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource)
{
	wrapped_interface->CopyResource(reinterpret_cast<d3d11_resource*>(pDstResource)->wrapped_interface, reinterpret_cast<d3d11_resource*>(pSrcResource)->wrapped_interface);
}

void wd::device_context_x::UpdateSubresource(ID3D11Resource* pDstResource, UINT DstSubresource,
	const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	wrapped_interface->UpdateSubresource(reinterpret_cast<d3d11_resource*>(pDstResource)->wrapped_interface, DstSubresource, pDstBox, pSrcData, SrcRowPitch,
	                                        SrcDepthPitch);
}

void wd::device_context_x::CopyStructureCount(ID3D11Buffer* pDstBuffer, UINT DstAlignedByteOffset,
	ID3D11UnorderedAccessView* pSrcView)
{
	wrapped_interface->CopyStructureCount(pDstBuffer, DstAlignedByteOffset, pSrcView);
}

void wd::device_context_x::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[ 4 ])
{

	if (pRenderTargetView == nullptr)
	{
		return;
	}
	wrapped_interface->ClearRenderTargetView(reinterpret_cast<wd::render_target_view*>(pRenderTargetView)->wrapped_interface, ColorRGBA);
}




void wd::device_context_x::ClearUnorderedAccessViewUint(ID3D11UnorderedAccessView* pUnorderedAccessView,
	const UINT Values[4])
{
	wrapped_interface->ClearUnorderedAccessViewUint(pUnorderedAccessView, Values);
}

void wd::device_context_x::ClearUnorderedAccessViewFloat(ID3D11UnorderedAccessView* pUnorderedAccessView,
	const FLOAT Values[4])
{
	wrapped_interface->ClearUnorderedAccessViewFloat(pUnorderedAccessView, Values);
}

void wd::device_context_x::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView, UINT ClearFlags,
	FLOAT Depth, UINT8 Stencil)
{
	wrapped_interface->ClearDepthStencilView(reinterpret_cast<wd::depth_stencil_view*>(pDepthStencilView)->wrapped_interface, ClearFlags, Depth, Stencil);
}

void wd::device_context_x::GenerateMips(ID3D11ShaderResourceView* pShaderResourceView)
{
	ID3D11ShaderResourceView* unwrappedSRV = nullptr;

	if (pShaderResourceView)
	{
		wdi::ID3D11ShaderResourceView* wdi_srv = nullptr;
		HRESULT hr = pShaderResourceView->QueryInterface(__uuidof(wdi::ID3D11ShaderResourceView),
														  reinterpret_cast<void**>(&wdi_srv));
		if (SUCCEEDED(hr) && wdi_srv)
		{
			auto wrapped = static_cast<wd::shader_resource_view*>(wdi_srv);
			unwrappedSRV = wrapped->wrapped_interface;
			wdi_srv->Release();
		}
		else
		{
			unwrappedSRV = pShaderResourceView; // passthrough if native
		}
	}

	wrapped_interface->GenerateMips(unwrappedSRV);
}

void wd::device_context_x::SetResourceMinLOD(ID3D11Resource* pResource, FLOAT MinLOD)
{
	wrapped_interface->SetResourceMinLOD(reinterpret_cast<d3d11_resource*>(pResource)->wrapped_interface, MinLOD);
}

FLOAT wd::device_context_x::GetResourceMinLOD(ID3D11Resource* pResource)
{
	return wrapped_interface->GetResourceMinLOD(reinterpret_cast<d3d11_resource*>(pResource)->wrapped_interface);
}

void wd::device_context_x::ResolveSubresource(ID3D11Resource* pDstResource, UINT DstSubresource,
	ID3D11Resource* pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format)
{
	wrapped_interface->ResolveSubresource(reinterpret_cast<d3d11_resource*>(pDstResource)->wrapped_interface, DstSubresource, reinterpret_cast<d3d11_resource*>(pSrcResource)->wrapped_interface, SrcSubresource, Format);
}

void wd::device_context_x::ExecuteCommandList(ID3D11CommandList* pCommandList, BOOL RestoreContextState)
{
	wrapped_interface->ExecuteCommandList(pCommandList, RestoreContextState);
}

void wd::device_context_x::HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	wrapped_interface->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	if (ppConstantBuffers != nullptr && *ppConstantBuffers != nullptr)
	{
		ID3D11Buffer* modifiedBuffers[ D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT ];
		for (UINT i = 0; i < NumBuffers; ++i)
		{
			modifiedBuffers[ i ] = reinterpret_cast<wd::buffer*>(ppConstantBuffers[ i ])->wrapped_interface;
		}
		wrapped_interface->HSSetConstantBuffers(StartSlot, NumBuffers, modifiedBuffers);
	}
	else
	{
		wrapped_interface->HSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
	}
}

void wd::device_context_x::DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	wrapped_interface->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	if (ppConstantBuffers != nullptr && *ppConstantBuffers != nullptr)
	{
		ID3D11Buffer* modifiedBuffers[ D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT ];
		for (UINT i = 0; i < NumBuffers; ++i)
		{
			modifiedBuffers[ i ] = reinterpret_cast<wd::buffer*>(ppConstantBuffers[ i ])->wrapped_interface;
		}
		wrapped_interface->DSSetConstantBuffers(StartSlot, NumBuffers, modifiedBuffers);
	}
	else {
		wrapped_interface->DSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
	}
}

void wd::device_context_x::CSSetUnorderedAccessViews(
	UINT StartSlot,
	UINT NumUAVs,
	ID3D11UnorderedAccessView* const* ppUnorderedAccessViews,
	const UINT* pUAVInitialCounts)
{
	ID3D11UnorderedAccessView* unwrappedUAVs[ D3D11_PS_CS_UAV_REGISTER_COUNT ] = {};

	for (UINT i = 0; i < NumUAVs; ++i)
	{
		if (ppUnorderedAccessViews && ppUnorderedAccessViews[ i ])
		{
			wdi::ID3D11UnorderedAccessView* wdi_uav = nullptr;
			HRESULT hr = ppUnorderedAccessViews[ i ]->QueryInterface(__uuidof(wdi::ID3D11UnorderedAccessView),
																   reinterpret_cast<void**>(&wdi_uav));
			if (SUCCEEDED(hr) && wdi_uav)
			{
				auto wrapped = static_cast<wd::unordered_access_view*>(wdi_uav);
				unwrappedUAVs[ i ] = wrapped->wrapped_interface;
				wdi_uav->Release();
			}
			else
			{
				unwrappedUAVs[ i ] = ppUnorderedAccessViews[ i ]; // passthrough if native
			}
		}
		else
		{
			unwrappedUAVs[ i ] = nullptr;
		}
	}

	wrapped_interface->CSSetUnorderedAccessViews(StartSlot, NumUAVs, unwrappedUAVs, pUAVInitialCounts);
}


void wd::device_context_x::CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	wrapped_interface->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	if (ppConstantBuffers != nullptr && *ppConstantBuffers != nullptr)
	{
		ID3D11Buffer* modifiedBuffers[ D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT ];
		for (UINT i = 0; i < NumBuffers; ++i) {
			modifiedBuffers[ i ] = reinterpret_cast<wd::buffer*>(ppConstantBuffers[ i ])->wrapped_interface;
		}
		wrapped_interface->CSSetConstantBuffers(StartSlot, NumBuffers, modifiedBuffers);
	}
	else
	{
		wrapped_interface->CSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
	}
}

void wd::device_context_x::VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	if (ppConstantBuffers != NULL)
	{
		ID3D11Buffer* unwrappedBuffers[ D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT ];

		wrapped_interface->VSGetConstantBuffers(StartSlot, NumBuffers, unwrappedBuffers);

		for (UINT i = 0; i < NumBuffers; ++i) {
			ppConstantBuffers[ i ] = reinterpret_cast<ID3D11Buffer*>(new wd::buffer(unwrappedBuffers[ i ]));
		}
	}
	else
	{
		wrapped_interface->VSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
	}
}

void wd::device_context_x::PSGetShaderResources(UINT StartSlot, UINT NumViews,
	ID3D11ShaderResourceView** ppShaderResourceViews)
{
	wrapped_interface->PSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void wd::device_context_x::PSGetShader(ID3D11PixelShader** ppPixelShader, ID3D11ClassInstance** ppClassInstances,
	UINT* pNumClassInstances)
{
	wrapped_interface->PSGetShader(ppPixelShader, ppClassInstances, pNumClassInstances);
}

void wd::device_context_x::PSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	wrapped_interface->PSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::VSGetShader(ID3D11VertexShader** ppVertexShader, ID3D11ClassInstance** ppClassInstances,
	UINT* pNumClassInstances)
{
	wrapped_interface->VSGetShader(ppVertexShader, ppClassInstances, pNumClassInstances);
}

void wd::device_context_x::PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	if (ppConstantBuffers != NULL)
	{
		ID3D11Buffer* unwrappedBuffers[ D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT ];

		wrapped_interface->PSGetConstantBuffers(StartSlot, NumBuffers, unwrappedBuffers);

		for (UINT i = 0; i < NumBuffers; ++i)
		{
			ppConstantBuffers[ i ] = reinterpret_cast<ID3D11Buffer*>(new wd::buffer(unwrappedBuffers[ i ]));
		}
	}
	else
	{
		wrapped_interface->PSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
	}
}

void wd::device_context_x::IAGetInputLayout(ID3D11InputLayout** ppInputLayout)
{
	wrapped_interface->IAGetInputLayout(ppInputLayout);
}

void wd::device_context_x::IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppVertexBuffers,
	UINT* pStrides, UINT* pOffsets)
{
	if (ppVertexBuffers != NULL)
	{
		ID3D11Buffer* unwrappedBuffers[ D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT ];

		wrapped_interface->IAGetVertexBuffers(StartSlot, NumBuffers, unwrappedBuffers, pStrides, pOffsets);

		for (UINT i = 0; i < NumBuffers; ++i)
		{
			ppVertexBuffers[ i ] = reinterpret_cast<ID3D11Buffer*>(new wd::buffer(unwrappedBuffers[ i ]));
		}
	}
	else
	{
		wrapped_interface->IAGetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
	}
}

void wd::device_context_x::IAGetIndexBuffer(ID3D11Buffer** pIndexBuffer, DXGI_FORMAT* Format, UINT* Offset)
{
	wrapped_interface->IAGetIndexBuffer(pIndexBuffer, Format, Offset);

	if (pIndexBuffer != nullptr)
	{
		*pIndexBuffer = pIndexBuffer
			? reinterpret_cast<ID3D11Buffer*>(new wd::buffer(*pIndexBuffer))
			: nullptr;
	}
}

void wd::device_context_x::GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	if (ppConstantBuffers != NULL)
	{
		ID3D11Buffer* unwrappedBuffers[ D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT ];

		wrapped_interface->GSGetConstantBuffers(StartSlot, NumBuffers, unwrappedBuffers);

		for (UINT i = 0; i < NumBuffers; ++i)
		{
			ppConstantBuffers[ i ] = reinterpret_cast<ID3D11Buffer*>(new wd::buffer(unwrappedBuffers[ i ]));
		}
	}
	else
	{
		wrapped_interface->GSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
	}
}

void wd::device_context_x::GSGetShader(ID3D11GeometryShader** ppGeometryShader, ID3D11ClassInstance** ppClassInstances,
	UINT* pNumClassInstances)
{
	wrapped_interface->GSGetShader(ppGeometryShader, ppClassInstances, pNumClassInstances);
}

void wd::device_context_x::IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY* pTopology)
{
	wrapped_interface->IAGetPrimitiveTopology(pTopology);
}

void wd::device_context_x::VSGetShaderResources(UINT StartSlot, UINT NumViews,
	ID3D11ShaderResourceView** ppShaderResourceViews)
{
	wrapped_interface->VSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void wd::device_context_x::VSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	wrapped_interface->VSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::GetPredication(ID3D11Predicate** ppPredicate, BOOL* pPredicateValue)
{
	wrapped_interface->GetPredication(ppPredicate, pPredicateValue);
}

void wd::device_context_x::GSGetShaderResources(UINT StartSlot, UINT NumViews,
	ID3D11ShaderResourceView** ppShaderResourceViews)
{
	wrapped_interface->GSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void wd::device_context_x::GSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	wrapped_interface->GSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::OMGetRenderTargets(UINT NumViews, ID3D11RenderTargetView** ppRenderTargetViews,
	ID3D11DepthStencilView** ppDepthStencilView)
{
	::ID3D11RenderTargetView* target = nullptr;
	::ID3D11DepthStencilView* depth = nullptr;
	wrapped_interface->OMGetRenderTargets(NumViews, &target, &depth);
	
	if (ppRenderTargetViews != nullptr)
	{
		*ppRenderTargetViews = ppRenderTargetViews
			? reinterpret_cast<ID3D11RenderTargetView*>(new
				render_target_view(target))
			: nullptr;
	}
	
	if (ppDepthStencilView != nullptr)
	{
		*ppDepthStencilView = ppDepthStencilView
			? reinterpret_cast<ID3D11DepthStencilView*>(new
				depth_stencil_view(depth))
			: nullptr;
	}
}

void wd::device_context_x::OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs,
	ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView** ppDepthStencilView, UINT UAVStartSlot,
	UINT NumUAVs, ID3D11UnorderedAccessView** ppUnorderedAccessViews)
{
	wrapped_interface->OMGetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, ppDepthStencilView,
	                                                                UAVStartSlot, NumUAVs, ppUnorderedAccessViews);
}

void wd::device_context_x::OMGetBlendState(ID3D11BlendState** ppBlendState, FLOAT BlendFactor[4], UINT* pSampleMask)
{
	wrapped_interface->OMGetBlendState(ppBlendState, BlendFactor, pSampleMask);
}

void wd::device_context_x::OMGetDepthStencilState(ID3D11DepthStencilState** ppDepthStencilState, UINT* pStencilRef)
{
	wrapped_interface->OMGetDepthStencilState(ppDepthStencilState, pStencilRef);
}

void wd::device_context_x::SOGetTargets(UINT NumBuffers, ID3D11Buffer** ppSOTargets)
{
	wrapped_interface->SOGetTargets(NumBuffers, ppSOTargets);
}

void wd::device_context_x::RSGetState(ID3D11RasterizerState** ppRasterizerState)
{
	wrapped_interface->RSGetState(ppRasterizerState);
}

void wd::device_context_x::RSGetViewports(UINT* pNumViewports, D3D11_VIEWPORT* pViewports)
{
	wrapped_interface->RSGetViewports(pNumViewports, pViewports);
}

void wd::device_context_x::RSGetScissorRects(UINT* pNumRects, D3D11_RECT* pRects)
{
	wrapped_interface->RSGetScissorRects(pNumRects, pRects);
}

void wd::device_context_x::HSGetShaderResources(UINT StartSlot, UINT NumViews,
	ID3D11ShaderResourceView** ppShaderResourceViews)
{
	wrapped_interface->HSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void wd::device_context_x::HSGetShader(ID3D11HullShader** ppHullShader, ID3D11ClassInstance** ppClassInstances,
	UINT* pNumClassInstances)
{
	wrapped_interface->HSGetShader(ppHullShader, ppClassInstances, pNumClassInstances);
}

void wd::device_context_x::HSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	wrapped_interface->HSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	wrapped_interface->HSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void wd::device_context_x::DSGetShaderResources(UINT StartSlot, UINT NumViews,
	ID3D11ShaderResourceView** ppShaderResourceViews)
{
	wrapped_interface->DSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void wd::device_context_x::DSGetShader(ID3D11DomainShader** ppDomainShader, ID3D11ClassInstance** ppClassInstances,
	UINT* pNumClassInstances)
{
	wrapped_interface->DSGetShader(ppDomainShader, ppClassInstances, pNumClassInstances);
}

void wd::device_context_x::DSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	wrapped_interface->DSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	wrapped_interface->DSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void wd::device_context_x::CSGetShaderResources(UINT StartSlot, UINT NumViews,
	ID3D11ShaderResourceView** ppShaderResourceViews)
{
	wrapped_interface->CSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void wd::device_context_x::CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs,
	ID3D11UnorderedAccessView** ppUnorderedAccessViews)
{
	wrapped_interface->CSGetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews);
}

void wd::device_context_x::CSGetShader(ID3D11ComputeShader** ppComputeShader, ID3D11ClassInstance** ppClassInstances,
	UINT* pNumClassInstances)
{
	wrapped_interface->CSGetShader(ppComputeShader, ppClassInstances, pNumClassInstances);
}

void wd::device_context_x::CSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	wrapped_interface->CSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	wrapped_interface->CSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void wd::device_context_x::ClearState()
{
	wrapped_interface->ClearState();
}

void wd::device_context_x::Flush()
{
	wrapped_interface->Flush();
}

D3D11_DEVICE_CONTEXT_TYPE wd::device_context_x::GetType()
{
	return wrapped_interface->GetType();
}

UINT wd::device_context_x::GetContextFlags()
{
	return wrapped_interface->GetContextFlags();
}

HRESULT wd::device_context_x::FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList** ppCommandList)
{
	return wrapped_interface->FinishCommandList(RestoreDeferredContextState, ppCommandList);
}

void wd::device_context_x::CopySubresourceRegion1(ID3D11Resource* pDstResource, UINT DstSubresource, UINT DstX,
	UINT DstY, UINT DstZ, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox, UINT CopyFlags)
{
	wrapped_interface->CopySubresourceRegion1(reinterpret_cast<d3d11_resource*>(pDstResource)->wrapped_interface, DstSubresource, DstX, DstY, DstZ, reinterpret_cast<d3d11_resource*>(pSrcResource)->wrapped_interface,
	                                             SrcSubresource, pSrcBox, CopyFlags);
}

void wd::device_context_x::UpdateSubresource1(ID3D11Resource* pDstResource, UINT DstSubresource,
	const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch, UINT CopyFlags)
{
	wrapped_interface->UpdateSubresource1(reinterpret_cast<d3d11_resource*>(pDstResource)->wrapped_interface, DstSubresource, pDstBox, pSrcData, SrcRowPitch,
	                                         SrcDepthPitch, CopyFlags);
}

void wd::device_context_x::DiscardResource(ID3D11Resource* pResource)
{
	wrapped_interface->DiscardResource(reinterpret_cast<d3d11_resource*>(pResource)->wrapped_interface);
}

void wd::device_context_x::DiscardView(ID3D11View* pResourceView)
{
	wrapped_interface->DiscardView(pResourceView);
}

void wd::device_context_x::VSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
	ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants)
{
	wrapped_interface->VSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::HSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
	ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants)
{
	wrapped_interface->
		HSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::DSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
	ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants)
{
	wrapped_interface->
		DSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::GSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
	ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants)
{
	wrapped_interface->
		GSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::PSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
	ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants)
{
	wrapped_interface->
		PSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::CSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers,
	ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants)
{
	wrapped_interface->
		CSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::VSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers,
	UINT* pFirstConstant, UINT* pNumConstants)
{
	wrapped_interface->
		VSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::HSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers,
	UINT* pFirstConstant, UINT* pNumConstants)
{
	wrapped_interface->
		HSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::DSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers,
	UINT* pFirstConstant, UINT* pNumConstants)
{
	wrapped_interface->
		DSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::GSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers,
	UINT* pFirstConstant, UINT* pNumConstants)
{
	wrapped_interface->
		GSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::PSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers,
	UINT* pFirstConstant, UINT* pNumConstants)
{
	wrapped_interface->
		PSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::CSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers,
	UINT* pFirstConstant, UINT* pNumConstants)
{
	wrapped_interface->
		CSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
}

void wd::device_context_x::SwapDeviceContextState(ID3DDeviceContextState* pState,
	ID3DDeviceContextState** ppPreviousState)
{
	wrapped_interface->SwapDeviceContextState(pState, ppPreviousState);
}

void wd::device_context_x::ClearView(ID3D11View* pView, const FLOAT Color[4], const D3D11_RECT* pRect, UINT NumRects)
{
	wrapped_interface->ClearView(pView, Color, pRect, NumRects);
}

void wd::device_context_x::DiscardView1(ID3D11View* pResourceView, const D3D11_RECT* pRects, UINT NumRects)
{
	wrapped_interface->DiscardView1(pResourceView, pRects, NumRects);
}

HRESULT wd::device_context_x::UpdateTileMappings(ID3D11Resource* pTiledResource, UINT NumTiledResourceRegions,
	const D3D11_TILED_RESOURCE_COORDINATE* pTiledResourceRegionStartCoordinates,
	const D3D11_TILE_REGION_SIZE* pTiledResourceRegionSizes, ID3D11Buffer* pTilePool, UINT NumRanges,
	const UINT* pRangeFlags, const UINT* pTilePoolStartOffsets, const UINT* pRangeTileCounts, UINT Flags)
{
	return wrapped_interface->UpdateTileMappings(reinterpret_cast<d3d11_resource*>(pTiledResource)->wrapped_interface, NumTiledResourceRegions,
	                                                pTiledResourceRegionStartCoordinates,
	                                                pTiledResourceRegionSizes, pTilePool, NumRanges, pRangeFlags,
	                                                pTilePoolStartOffsets,
	                                                pRangeTileCounts, Flags);
}

HRESULT wd::device_context_x::CopyTileMappings(ID3D11Resource* pDestTiledResource,
	const D3D11_TILED_RESOURCE_COORDINATE* pDestRegionStartCoordinate, ID3D11Resource* pSourceTiledResource,
	const D3D11_TILED_RESOURCE_COORDINATE* pSourceRegionStartCoordinate, const D3D11_TILE_REGION_SIZE* pTileRegionSize,
	UINT Flags)
{
	return wrapped_interface->CopyTileMappings(reinterpret_cast<d3d11_resource*>(pDestTiledResource)->wrapped_interface, pDestRegionStartCoordinate, reinterpret_cast<d3d11_resource*>(pSourceTiledResource)->wrapped_interface,
	                                              pSourceRegionStartCoordinate,
	                                              pTileRegionSize, Flags);
}

void wd::device_context_x::CopyTiles(ID3D11Resource* pTiledResource,
	const D3D11_TILED_RESOURCE_COORDINATE* pTileRegionStartCoordinate, const D3D11_TILE_REGION_SIZE* pTileRegionSize,
	ID3D11Buffer* pBuffer, UINT64 BufferStartOffsetInBytes, UINT Flags)
{
	wrapped_interface->CopyTiles(reinterpret_cast<d3d11_resource*>(pTiledResource)->wrapped_interface, pTileRegionStartCoordinate, pTileRegionSize, pBuffer,
	                                BufferStartOffsetInBytes, Flags);
}

void wd::device_context_x::UpdateTiles(ID3D11Resource* pDestTiledResource,
	const D3D11_TILED_RESOURCE_COORDINATE* pDestTileRegionStartCoordinate,
	const D3D11_TILE_REGION_SIZE* pDestTileRegionSize, const void* pSourceTileData, UINT Flags)
{
	wrapped_interface->UpdateTiles(reinterpret_cast<d3d11_resource*>(pDestTiledResource)->wrapped_interface, pDestTileRegionStartCoordinate, pDestTileRegionSize,
	                                  pSourceTileData, Flags);
}

HRESULT wd::device_context_x::ResizeTilePool(ID3D11Buffer* pTilePool, UINT64 NewSizeInBytes)
{
	return wrapped_interface->ResizeTilePool(pTilePool, NewSizeInBytes);
}

void wd::device_context_x::TiledResourceBarrier(ID3D11DeviceChild* pTiledResourceOrViewAccessBeforeBarrier,
	ID3D11DeviceChild* pTiledResourceOrViewAccessAfterBarrier)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
	//wrapped_interface->TiledResourceBarrier(pTiledResourceOrViewAccessBeforeBarrier,
	//                                           pTiledResourceOrViewAccessAfterBarrier);
}

INT wd::device_context_x::PIXBeginEvent(LPCWSTR Name)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

INT wd::device_context_x::PIXBeginEventEx(const void* pData, UINT DataSize)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

INT wd::device_context_x::PIXEndEvent()
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::PIXSetMarker(LPCWSTR Name)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::PIXSetMarkerEx(const void* pData, UINT DataSize)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

BOOL wd::device_context_x::PIXGetStatus()
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::PIXGpuCaptureNextFrame(UINT Flags, LPCWSTR lpOutputFileName)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::PIXGpuBeginCapture(UINT Flags, LPCWSTR lpOutputFileName)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::PIXGpuEndCapture()
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::StartCounters(wdi::ID3D11CounterSetX* pCounterSet)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::SampleCounters(wdi::ID3D11CounterSampleX* pCounterSample)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::StopCounters()
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::GetCounterData(wdi::ID3D11CounterSampleX* pCounterSample, wdi::D3D11X_COUNTER_DATA* pData,
	UINT GetCounterDataFlags)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::FlushGpuCaches(ID3D11Resource* pResource)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::FlushGpuCacheRange(UINT Flags, void* pBaseAddress, SIZE_T SizeInBytes)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::InsertWaitUntilIdle(UINT Flags)
{
	LOG_NOT_IMPLEMENTED();
	// FIXME: implement, stubbing this seems to be fine for now
}

UINT64 wd::device_context_x::InsertFence(UINT Flags)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::InsertWaitOnFence(UINT Flags, UINT64 Fence)
{
	LOG_NOT_IMPLEMENTED();
	// FIXME: implement, stubbing this seems to be fine for now
}

void wd::device_context_x::RemapConstantBufferInheritance(wdi::D3D11_STAGE Stage, UINT Slot,
	wdi::D3D11_STAGE InheritStage, UINT InheritSlot)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::RemapShaderResourceInheritance(wdi::D3D11_STAGE Stage, UINT Slot,
	wdi::D3D11_STAGE InheritStage, UINT InheritSlot)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::RemapSamplerInheritance(wdi::D3D11_STAGE Stage, UINT Slot, wdi::D3D11_STAGE InheritStage,
	UINT InheritSlot)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::RemapVertexBufferInheritance(UINT Slot, UINT InheritSlot)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::PSSetFastConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::PSSetFastShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::PSSetFastSampler(UINT Slot, ID3D11SamplerState* pSampler)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::VSSetFastConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::VSSetFastShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::VSSetFastSampler(UINT Slot, ID3D11SamplerState* pSampler)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::GSSetFastConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::GSSetFastShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::GSSetFastSampler(UINT Slot, ID3D11SamplerState* pSampler)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::CSSetFastConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::CSSetFastShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::CSSetFastSampler(UINT Slot, ID3D11SamplerState* pSampler)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::HSSetFastConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::HSSetFastShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::HSSetFastSampler(UINT Slot, ID3D11SamplerState* pSampler)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::DSSetFastConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::DSSetFastShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::DSSetFastSampler(UINT Slot, ID3D11SamplerState* pSampler)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::IASetFastVertexBuffer(UINT Slot, ID3D11Buffer* pVertexBuffer, UINT Stride)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::IASetFastIndexBuffer(UINT HardwareIndexFormat, ID3D11Buffer* pIndexBuffer)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::PSSetPlacementConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer, void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::PSSetPlacementShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView,
	void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::VSSetPlacementConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer, void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::VSSetPlacementShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView,
	void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::GSSetPlacementConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer, void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::GSSetPlacementShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView,
	void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::CSSetPlacementConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer, void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::CSSetPlacementShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView,
	void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::HSSetPlacementConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer, void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::HSSetPlacementShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView,
	void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::DSSetPlacementConstantBuffer(UINT Slot, ID3D11Buffer* pConstantBuffer, void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::DSSetPlacementShaderResource(UINT Slot, ID3D11ShaderResourceView* pShaderResourceView,
	void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::IASetPlacementVertexBuffer(UINT Slot, ID3D11Buffer* pVertexBuffer, void* pBaseAddress,
	UINT Stride)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::IASetPlacementIndexBuffer(UINT HardwareIndexFormat, ID3D11Buffer* pIndexBuffer,
	void* pBaseAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::HSSetTessellationParameters(
	const wdi::D3D11X_TESSELLATION_PARAMETERS* pTessellationParameters)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::HSGetLastUsedTessellationParameters(
	wdi::D3D11X_TESSELLATION_PARAMETERS* pTessellationParameters)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::CSEnableAutomaticGpuFlush(BOOL Enable)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::GpuSendPipelinedEvent(wdi::D3D11X_GPU_PIPELINED_EVENT Event)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::Suspend(UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::Resume()
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::BeginCommandListExecution(UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::EndCommandListExecution()
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetGraphicsShaderLimits(const wdi::D3D11X_GRAPHICS_SHADER_LIMITS* pShaderLimits)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetComputeShaderLimits(const wdi::D3D11X_COMPUTE_SHADER_LIMITS* pShaderLimits)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetPredicationBuffer(ID3D11Buffer* pBuffer, UINT Offset, UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::OMSetDepthBounds(FLOAT min, FLOAT max)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::OMSetDepthStencilStateX(ID3D11DepthStencilState* pDepthStencilState)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::OMSetSampleMask(UINT64 QuadSampleMask)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

UINT32* wd::device_context_x::MakeCeSpace()
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetFastResources_Debug(UINT* pTableStart, UINT* pTableEnd)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::BeginResourceBatch(void* pBuffer, UINT BufferSize)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

UINT wd::device_context_x::EndResourceBatch(UINT* pSizeNeeded)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetFastResourcesFromBatch_Debug(void* pBatch, UINT Size)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::CSPlaceUnorderedAccessView(UINT Slot,
	wdi::D3D11X_DESCRIPTOR_UNORDERED_ACCESS_VIEW* const pDescriptor, UINT64 Offset)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::WriteValueEndOfPipe(void* pDestination, UINT Value, UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::CopyMemoryToMemory(void* pDstAddress, void* pSrcAddress, SIZE_T SizeBytes)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::FillMemoryWithValue(void* pDstAddress, SIZE_T SizeBytes, UINT FillValue)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::BeginProcessVideoResource(ID3D11Resource* pResource, UINT SubResource)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::EndProcessVideoResource(ID3D11Resource* pResource, UINT SubResource)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::StartThreadTrace(const wdi::D3D11X_THREAD_TRACE_DESC* pDesc,
	void* pDstAddressShaderEngine0, void* pDstAddressShaderEngine1, SIZE_T BufferSizeBytes)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::StopThreadTrace(void* pDstAddressTraceSize)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::InsertThreadTraceMarker(UINT Marker)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::IASetPrimitiveResetIndex(UINT ResetIndex)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetShaderResourceViewMinLOD(ID3D11ShaderResourceView* pShaderResourceView, FLOAT MinLOD)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::InsertWaitOnPresent(UINT Flags, ID3D11Resource* pBackBuffer)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::ClearRenderTargetViewX(ID3D11RenderTargetView* pRenderTargetView, UINT Flags,
												  const FLOAT ColorRGBA[ 4 ])
{
	if (!pRenderTargetView)
	{
		LOG_ERROR("[ClearRenderTargetViewX] ERROR: pRenderTargetView is null!\n");
		return;
	}

	if (!ColorRGBA)
	{
		LOG_ERROR("[ClearRenderTargetViewX] ERROR: ColorRGBA is null!\n");
		return;
	}

	// Assuming wrapped_interface is your internal ID3D11DeviceContext*
	wrapped_interface->ClearRenderTargetView(pRenderTargetView, ColorRGBA);

	if (Flags != 0)
	{
		// If you're implementing custom flags (X extensions), handle them here.
		LOG_WARNING("[ClearRenderTargetViewX] Flags were passed, but are not handled: 0x%X\n", Flags);
	}
}


UINT wd::device_context_x::GetResourceCompression(ID3D11Resource* pResource)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

UINT wd::device_context_x::GetResourceCompressionX(const wdi::D3D11X_DESCRIPTOR_RESOURCE* pResource)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::DecompressResource(ID3D11Resource* pDstResource, UINT DstSubresource,
	const wdi::D3D11X_POINT* pDstPoint, ID3D11Resource* pSrcResource, UINT SrcSubresource,
	const wdi::D3D11X_RECT* pSrcRect, DXGI_FORMAT DecompressFormat, UINT DecompressFlags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::DecompressResourceX(wdi::D3D11X_DESCRIPTOR_RESOURCE* pDstResource, UINT DstSubresource,
	const wdi::D3D11X_POINT* pDstPoint, wdi::D3D11X_DESCRIPTOR_RESOURCE* pSrcResource, UINT SrcSubresource,
	const wdi::D3D11X_RECT* pSrcRect, wdi::D3D11X_FORMAT DecompressFormat, UINT DecompressFlags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::GSSetParameters(const wdi::D3D11X_GS_PARAMETERS* pGsParameters)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::GSGetLastUsedParameters(wdi::D3D11X_GS_PARAMETERS* pGsParameters)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::MultiDrawIndexedInstancedIndirect(UINT PrimitiveCount, ID3D11Buffer* pBufferForArgs,
	UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::MultiDrawInstancedIndirect(UINT PrimitiveCount, ID3D11Buffer* pBufferForArgs,
	UINT AlignedByteOffsetForArgs, UINT StrideByteOffsetForArgs, UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::MultiDrawIndexedInstancedIndirectAuto(ID3D11Buffer* pBufferForPrimitiveCount,
	UINT AlignedByteOffsetForPrimitiveCount, ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs,
	UINT StrideByteOffsetForArgs, UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::MultiDrawInstancedIndirectAuto(ID3D11Buffer* pBufferForPrimitiveCount,
	UINT AlignedByteOffsetForPrimitiveCount, ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs,
	UINT StrideByteOffsetForArgs, UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

HRESULT wd::device_context_x::RSGetMSAASettingsForQuality(wdi::D3D11X_MSAA_SCAN_CONVERTER_SETTINGS* pMSAASCSettings,
	wdi::D3D11X_MSAA_EQAA_SETTINGS* pEQAASettings, wdi::D3D11X_MSAA_SAMPLE_PRIORITIES* pCentroidPriorities,
	wdi::D3D11X_MSAA_SAMPLE_POSITIONS* pSamplePositions, UINT LogSampleCount, UINT SampleQuality)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::RSSetScanConverterMSAASettings(
	const wdi::D3D11X_MSAA_SCAN_CONVERTER_SETTINGS* pMSAASCSettings)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::RSSetEQAASettings(const wdi::D3D11X_MSAA_EQAA_SETTINGS* pEQAASettings)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::RSSetSamplePositions(const wdi::D3D11X_MSAA_SAMPLE_PRIORITIES* pSamplesPriorities,
	const wdi::D3D11X_MSAA_SAMPLE_POSITIONS* pSamplePositions)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetResourceCompression(ID3D11Resource* pResource, UINT Compression)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetResourceCompressionX(const wdi::D3D11X_DESCRIPTOR_RESOURCE* pResource, UINT Compression)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetGDSRange(wdi::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::WriteGDS(wdi::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords,
	const UINT* pCounterValues, UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::ReadGDS(wdi::D3D11X_GDS_REGION_TYPE RegionType, UINT OffsetDwords, UINT NumDwords,
	UINT* pCounterValues, UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::VSSetShaderUserData(UINT StartSlot, UINT NumRegisters, const UINT* pData)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::HSSetShaderUserData(UINT StartSlot, UINT NumRegisters, const UINT* pData)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::DSSetShaderUserData(UINT StartSlot, UINT NumRegisters, const UINT* pData)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::GSSetShaderUserData(UINT StartSlot, UINT NumRegisters, const UINT* pData)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::PSSetShaderUserData(UINT StartSlot, UINT NumRegisters, const UINT* pData)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::CSSetShaderUserData(UINT StartSlot, UINT NumRegisters, const UINT* pData)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::InsertWaitOnMemory(const void* pAddress, UINT Flags,
	D3D11_COMPARISON_FUNC ComparisonFunction, UINT ReferenceValue, UINT Mask)
{
	LOG_NOT_IMPLEMENTED();
	// FIXME: implement, stubbing this seems to be fine for now
}

void wd::device_context_x::WriteTimestampToMemory(void* pDstAddress)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::WriteTimestampToBuffer(ID3D11Buffer* pBuffer, UINT OffsetBytes)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::StoreConstantRam(UINT Flags, ID3D11Buffer* pBuffer, UINT BufferOffsetInBytes,
	UINT CeRamOffsetInBytes, UINT SizeInBytes)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::LoadConstantRam(UINT Flags, ID3D11Buffer* pBuffer, UINT BufferOffsetInBytes,
	UINT CeRamOffsetInBytes, UINT SizeInBytes)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::WriteQuery(D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags, ID3D11Buffer* pBuffer,
	UINT OffsetInBytes, UINT StrideInBytes)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::ResetQuery(D3D11_QUERY QueryType, UINT QueryIndex, UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::ConfigureQuery(D3D11_QUERY QueryType, const void* pConfiguration, UINT ConfigurationSize)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetShaderUserData(wdi::D3D11X_HW_STAGE ShaderStage, UINT StartSlot, UINT NumRegisters,
	const UINT* pData)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetPixelShaderDepthForceZOrder(BOOL ForceOrder)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetPredicationFromQuery(D3D11_QUERY QueryType, ID3D11Buffer* pBuffer, UINT OffsetInBytes,
	UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetBorderColorPalette(ID3D11Buffer* pBuffer, UINT OffsetInBytes, UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::WriteValueEndOfPipe64(void* pDestination, UINT64 Value, UINT Flags)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::InsertWaitOnMemory64(const void* pAddress, UINT Flags,
	D3D11_COMPARISON_FUNC ComparisonFunction, UINT64 ReferenceValue)
{
	// FIXME: implement, stubbing this seems to be fine for now
}

void wd::device_context_x::LoadConstantRamImmediate(UINT Flags, const void* pBuffer, UINT CeRamOffsetInBytes,
	UINT SizeInBytes)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetScreenExtentsQuery(UINT Value)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::CollectScreenExtents(UINT Flags, UINT AddressCount, const UINT64* pDestinationAddresses,
	USHORT ZMin, USHORT ZMax)
{
		LOG_NOT_IMPLEMENTED();
		throw std::logic_error("Not implemented");
}

void wd::device_context_x::FillResourceWithValue(ID3D11Resource* pDstResource, UINT FillValue)
{
	LOG_NOT_IMPLEMENTED();

	throw std::logic_error("Not implemented");
}

void wd::device_context_x::SetDrawBalancing(UINT BalancingMode, UINT Flags)
{
	LOG_NOT_IMPLEMENTED();
	throw std::logic_error("Not implemented");
}

void wd::device_context_x::PSSetShaderResources(ID3D11ShaderResourceView* const* ppShaderResourceViews, UINT StartSlot,
	UINT PacketHeader)
{
	UINT NumViews = (PacketHeader >> 19) + 1;

	if (ppShaderResourceViews != NULL)
	{
		ID3D11ShaderResourceView* modifiedViews[ D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT ];

		for (UINT i = 0; i < NumViews; i++)
		{
			if (ppShaderResourceViews[ i ] == nullptr)
				modifiedViews[ i ] = nullptr;
			else
				modifiedViews[ i ] = reinterpret_cast<shader_resource_view*>(ppShaderResourceViews[ i ])->wrapped_interface;
		}
		wrapped_interface->PSSetShaderResources(StartSlot, NumViews, modifiedViews);
	}
	else
	{
		wrapped_interface->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}

void wd::device_context_x::PSSetShader(ID3D11PixelShader* pPixelShader)
{
	wrapped_interface->PSSetShader(pPixelShader, nullptr, 0);
}

void wd::device_context_x::PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	wrapped_interface->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void wd::device_context_x::VSSetShader(ID3D11VertexShader* pVertexShader)
{
	wrapped_interface->VSSetShader(pVertexShader, nullptr, 0);
}

void wd::device_context_x::DrawIndexed(UINT64 StartIndexLocationAndIndexCount, INT BaseVertexLocation)
{
	UINT StartIndexLocation = static_cast<UINT>(StartIndexLocationAndIndexCount & 0xFFFFFFFF);
	UINT IndexCount = static_cast<UINT>((StartIndexLocationAndIndexCount >> 32) & 0xFFFFFFFF);

	ProcessDirtyFlags();
	wrapped_interface->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

// this function changes prototype on different sdk versions
void wd::device_context_x::IASetIndexBuffer(UINT HardwareIndexFormat, ID3D11Buffer* pIndexBuffer, UINT Offset)
{
	DXGI_FORMAT Format = HardwareIndexFormat == 1 ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;

	if (pIndexBuffer == nullptr)
	{
		return wrapped_interface->IASetIndexBuffer(pIndexBuffer, Format, Offset);
	}

	wrapped_interface->IASetIndexBuffer(reinterpret_cast<wd::buffer*>(pIndexBuffer)->wrapped_interface, Format, Offset);
}

void wd::device_context_x::DrawIndexedInstanced(UINT64 StartIndexLocationAndIndexCountPerInstance,
	UINT64 BaseVertexLocationAndStartInstanceLocation, UINT InstanceCount)
{
	UINT StartIndexLocation = static_cast<UINT>(StartIndexLocationAndIndexCountPerInstance & 0xFFFFFFFF);
	UINT IndexCountPerInstance = static_cast<UINT>((StartIndexLocationAndIndexCountPerInstance >> 32) &
		0xFFFFFFFF);

	UINT BaseVertexLocation = static_cast<UINT>(BaseVertexLocationAndStartInstanceLocation & 0xFFFFFFFF);
	UINT StartInstanceLocation = static_cast<UINT>((BaseVertexLocationAndStartInstanceLocation >> 32) &
		0xFFFFFFFF);

	ProcessDirtyFlags();
	wrapped_interface->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation,
										  BaseVertexLocation, StartInstanceLocation);
}

void wd::device_context_x::DrawInstanced(UINT VertexCountPerInstance,
	UINT64 StartVertexLocationAndStartInstanceLocation, UINT InstanceCount)
{
	UINT StartVertexLocation = static_cast<UINT>(StartVertexLocationAndStartInstanceLocation & 0xFFFFFFFF);
	UINT StartInstanceLocation = static_cast<UINT>((StartVertexLocationAndStartInstanceLocation >> 32) &
		0xFFFFFFFF);

	ProcessDirtyFlags();
	wrapped_interface->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation,
								   StartInstanceLocation);
}
