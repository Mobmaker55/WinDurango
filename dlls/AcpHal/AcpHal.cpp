// AcpHal.cpp
#include "pch.h"
#include "AcpHal.h"

#include <basetyps.h>
#include <cstdio>
#include <stdlib.h>
#include "contexts.h"
#include <intsafe.h>
#include <new>
<<<<<<< Updated upstream
//#include "../common/DebugLogger.h"

static APU_HEAP g_ApuHeap = { 0 };
HRESULT AcpHalAllocateShapeContexts_X(SHAPE_CONTEXTS* ctx) {
    if (!ctx)
        return E_INVALIDARG;

    memset(ctx, 0, sizeof(SHAPE_CONTEXTS));

    if (ctx->numSrcContexts > 0)
        ctx->srcContextArray = static_cast<SHAPE_SRC_CONTEXT*>(malloc(sizeof(SHAPE_SRC_CONTEXT) * ctx->numSrcContexts));

    if (ctx->numEqCompContexts > 0)
        ctx->eqCompContextArray = static_cast<SHAPE_EQCOMP_CONTEXT*>(malloc(sizeof(SHAPE_EQCOMP_CONTEXT) * ctx->numEqCompContexts));

    if (ctx->numFiltVolContexts > 0)
        ctx->filtVolContextArray = static_cast<SHAPE_FILTVOL_CONTEXT*>(malloc(sizeof(SHAPE_FILTVOL_CONTEXT) * ctx->numFiltVolContexts));

    if (ctx->numDmaContexts > 0)
        ctx->dmaContextArray = static_cast<SHAPE_DMA_CONTEXT*>(malloc(sizeof(SHAPE_DMA_CONTEXT) * ctx->numDmaContexts));

    if (ctx->numXmaContexts > 0)
        ctx->xmaContextArray = static_cast<SHAPE_XMA_CONTEXT*>(malloc(sizeof(SHAPE_XMA_CONTEXT) * ctx->numXmaContexts));

    if (ctx->numPcmContexts > 0)
        ctx->pcmContextArray = static_cast<SHAPE_PCM_CONTEXT*>(malloc(sizeof(SHAPE_PCM_CONTEXT) * ctx->numPcmContexts));

    printf("[AcpHalAllocateShapeContexts_X] Allocated shape context arrays."); 
    return S_OK;
}


<<<<<<< Updated upstream
HRESULT AcpHalReleaseShapeContexts_X() {
    //DEBUG_LOG();

    // Free any previously allocated context arrays
    if (g_ApuHeap.NonCached) {
        free(g_ApuHeap.NonCached);
        g_ApuHeap.NonCached = NULL;
        g_ApuHeap.NonCachedSize = 0;
    }

    if (g_ApuHeap.Cached) {
        free(g_ApuHeap.Cached);
        g_ApuHeap.Cached = NULL;
        g_ApuHeap.CachedSize = 0;
    }
    printf("[AcpHal] released shape context memory and reset heap");
    return S_OK;
}

HRESULT __stdcall AcpHalCreate_X(IAcpHal** acpInterface)
{
    if (!acpInterface)
        return E_POINTER;

    AcpHal* instance = new (std::nothrow) AcpHal();
    if (!instance)
        return E_OUTOFMEMORY;

    *acpInterface = instance;
    printf("[AcpHalCreate_X] IAcpHal interface created successfully.\n");
    return S_OK;
}



HRESULT ApuAlloc_X(
    void** virtualAddress,
    APU_ADDRESS* physicalAddress,
    UINT32 sizeInBytes,
    UINT32 alignmentInBytes,
    UINT32 flags
)
{
    if (!virtualAddress || sizeInBytes == 0 || alignmentInBytes == 0)
        return E_INVALIDARG;

    if ((alignmentInBytes & (alignmentInBytes - 1)) != 0 || alignmentInBytes < 4)
        return E_INVALIDARG;

    if ((flags != APU_ALLOC_CACHED) && (flags != APU_ALLOC_NONCACHED))
        return E_INVALIDARG;

    // Use aligned malloc for safe CPU-side simulation
    void* alignedPtr = _aligned_malloc(sizeInBytes, alignmentInBytes);
    if (!alignedPtr)
        return E_OUTOFMEMORY;

    *virtualAddress = alignedPtr;

    // Simulate physical address (if needed)
    if (physicalAddress)
        *physicalAddress = reinterpret_cast<APU_ADDRESS>(alignedPtr);

    printf("[ApuAlloc_X] Allocated %u bytes at 0x%p (aligned to %u bytes), flags=0x%X, phys=0x%llX\n",
        sizeInBytes, alignedPtr, alignmentInBytes, flags,
        physicalAddress ? *physicalAddress : 0);

    return S_OK;
}

HRESULT __stdcall ApuCreateHeap_X(UINT32 cachedSizeInBytes, UINT32 nonCachedSizeInBytes)
{
    if (g_ApuHeap.Cached || g_ApuHeap.NonCached) {
        return E_FAIL; // already initialized
    }

    g_ApuHeap.Cached = cachedSizeInBytes > 0 ? malloc(cachedSizeInBytes) : NULL;
    g_ApuHeap.NonCached = nonCachedSizeInBytes > 0 ? malloc(nonCachedSizeInBytes) : NULL;

    if ((cachedSizeInBytes && !g_ApuHeap.Cached) || (nonCachedSizeInBytes && !g_ApuHeap.NonCached)) {
        if (g_ApuHeap.Cached) free(g_ApuHeap.Cached);
        if (g_ApuHeap.NonCached) free(g_ApuHeap.NonCached);
        g_ApuHeap.Cached = NULL;
        g_ApuHeap.NonCached = NULL;
        g_ApuHeap.CachedSize = 0;
        g_ApuHeap.NonCachedSize = 0;
        return E_OUTOFMEMORY;
    }

    g_ApuHeap.CachedSize = cachedSizeInBytes;
    g_ApuHeap.NonCachedSize = nonCachedSizeInBytes;
    return S_OK;
}

HRESULT __stdcall ApuHeapGetState_X(ApuHeapState* apuHeapState, UINT32 flags)
{
<<<<<<< Updated upstream
    //DEBUG_LOG();

    if (!apuHeapState)
        return E_POINTER;

    apuHeapState->bytesFree = 0; // Not tracked
    apuHeapState->bytesAllocated = g_ApuHeap.CachedSize + g_ApuHeap.NonCachedSize;
    apuHeapState->bytesLost = 0; // Not tracked
    apuHeapState->maximumBlockSizeAvailable = 0; // Not tracked
    apuHeapState->allocationCount = 0; // Not tracked

    return S_OK;
}

bool ApuIsVirtualAddressValid_X(
         const void* virtualAddress,
         UINT32 physicalAlignmentInBytes
)
{
<<<<<<< Updated upstream
    //DEBUG_LOG();

    if (!virtualAddress || physicalAlignmentInBytes == 0)
        return false;

    uintptr_t addr = reinterpret_cast<uintptr_t>(virtualAddress);
    bool isAligned = (addr % physicalAlignmentInBytes) == 0;
    return isAligned;
}

HRESULT ApuFree_X(void* virtualAddress)
{
    if (!virtualAddress)
        return E_INVALIDARG;

    _aligned_free(virtualAddress);
    printf("[ApuFree_X] Freed memory at 0x%p\n", virtualAddress);
    return S_OK;
}

APU_ADDRESS __stdcall ApuMapVirtualAddress_X(const void* virtualAddress) {
<<<<<<< Updated upstream
    //DEBUG_LOG();
    return reinterpret_cast<APU_ADDRESS>(virtualAddress);
}

void* ApuMapApuAddress_X(
         APU_ADDRESS apuPhysicalAddress
)
{
<<<<<<< Updated upstream
    //DEBUG_LOG();
    return reinterpret_cast<void*>(apuPhysicalAddress);
}
