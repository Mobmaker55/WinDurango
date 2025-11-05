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

#include <Windows.h>
#include <mfapi.h>
// note from unixian: this proxy dll situation is temporary, but we need to use the actual functions from mfplat.dll while we're also named mfplat
#pragma region Proxy
struct mfplat_dll {
	HMODULE dll;
	FARPROC oCopyPropVariant;
	FARPROC oCreatePropVariant;
	FARPROC oCreatePropertyStore;
	FARPROC oDestroyPropVariant;
	FARPROC oGetAMSubtypeFromD3DFormat;
	FARPROC oGetD3DFormatFromMFSubtype;
	FARPROC oLFGetGlobalPool;
	FARPROC oMFAddPeriodicCallback;
	FARPROC oMFAllocateSerialWorkQueue;
	FARPROC oMFAllocateWorkQueue;
	FARPROC oMFAllocateWorkQueueEx;
	FARPROC oMFAppendCollection;
	FARPROC oMFAverageTimePerFrameToFrameRate;
	FARPROC oMFBeginCreateFile;
	FARPROC oMFBlockThread;
	FARPROC oMFCalculateBitmapImageSize;
	FARPROC oMFCalculateImageSize;
	FARPROC oMFCancelCreateFile;
	FARPROC oMFCancelWorkItem;
	FARPROC oMFConvertColorInfoFromDXVA;
	FARPROC oMFConvertColorInfoToDXVA;
	FARPROC oMFConvertFromFP16Array;
	FARPROC oMFConvertToFP16Array;
	FARPROC oMFCopyImage;
	FARPROC oMFCreate2DMediaBuffer;
	FARPROC oMFCreateAMMediaTypeFromMFMediaType;
	FARPROC oMFCreateAlignedMemoryBuffer;
	FARPROC oMFCreateAsyncResult;
	FARPROC oMFCreateAttributes;
	FARPROC oMFCreateAudioMediaType;
	FARPROC oMFCreateCollection;
	FARPROC oMFCreateDXGIDeviceManager;
	FARPROC oMFCreateDXGISurfaceBufferX;
	FARPROC oMFCreateDxvaSampleRendererX;
	FARPROC oMFCreateEventQueue;
	FARPROC oMFCreateFile;
	FARPROC oMFCreateFileFromHandle;
	FARPROC oMFCreateLegacyMediaBufferOnMFMediaBuffer;
	FARPROC oMFCreateMFByteStreamOnStream;
	FARPROC oMFCreateMFVideoFormatFromMFMediaType;
	FARPROC oMFCreateMediaBufferFromMediaType;
	FARPROC oMFCreateMediaBufferWrapper;
	FARPROC oMFCreateMediaEvent;
	FARPROC oMFCreateMediaEventResult;
	FARPROC oMFCreateMediaType;
	FARPROC oMFCreateMediaTypeFromRepresentation;
	FARPROC oMFCreateMemoryBuffer;
	FARPROC oMFCreateMemoryStream;
	FARPROC oMFCreateNV12ToRGB32ConverterX;
	FARPROC oMFCreatePathFromURL;
	FARPROC oMFCreatePresentationDescriptor;
	FARPROC oMFCreateRGB32ToNV12ConverterX;
	FARPROC oMFCreateSample;
	FARPROC oMFCreateSourceResolver;
	FARPROC oMFCreateSourceResolverInternal;
	FARPROC oMFCreateStreamDescriptor;
	FARPROC oMFCreateSystemTimeSource;
	FARPROC oMFCreateTempFile;
	FARPROC oMFCreateTrackedSample;
	FARPROC oMFCreateURLFromPath;
	FARPROC oMFCreateVideoMediaType;
	FARPROC oMFCreateVideoMediaTypeFromBitMapInfoHeader;
	FARPROC oMFCreateVideoMediaTypeFromBitMapInfoHeaderEx;
	FARPROC oMFCreateVideoMediaTypeFromSubtype;
	FARPROC oMFCreateVideoMediaTypeFromVideoInfoHeader;
	FARPROC oMFCreateVideoMediaTypeFromVideoInfoHeader2;
	FARPROC oMFCreateVideoSampleAllocatorEx;
	FARPROC oMFCreateWaveFormatExFromMFMediaType;
	FARPROC oMFDeserializeAttributesFromStream;
	FARPROC oMFDeserializeEvent;
	FARPROC oMFDeserializeMediaTypeFromStream;
	FARPROC oMFDeserializePresentationDescriptor;
	FARPROC oMFEndCreateFile;
	FARPROC oMFFrameRateToAverageTimePerFrame;
	FARPROC oMFGetAttributesAsBlob;
	FARPROC oMFGetAttributesAsBlobSize;
	FARPROC oMFGetConfigurationDWORD;
	FARPROC oMFGetConfigurationPolicy;
	FARPROC oMFGetConfigurationStore;
	FARPROC oMFGetConfigurationString;
	FARPROC oMFGetPlaneSize;
	FARPROC oMFGetPlatform;
	FARPROC oMFGetPrivateWorkqueues;
	FARPROC oMFGetStrideForBitmapInfoHeader;
	FARPROC oMFGetSupportedMimeTypes;
	FARPROC oMFGetSupportedSchemes;
	FARPROC oMFGetSystemTime;
	FARPROC oMFGetTimerPeriodicity;
	FARPROC oMFGetUncompressedVideoFormat;
	FARPROC oMFGetWorkQueueMMCSSTaskId;
	FARPROC oMFHeapAlloc;
	FARPROC oMFHeapFree;
	FARPROC oMFInitAMMediaTypeFromMFMediaType;
	FARPROC oMFInitAttributesFromBlob;
	FARPROC oMFInitMediaTypeFromAMMediaType;
	FARPROC oMFInitMediaTypeFromMFVideoFormat;
	FARPROC oMFInitMediaTypeFromVideoInfoHeader;
	FARPROC oMFInitMediaTypeFromVideoInfoHeader2;
	FARPROC oMFInitMediaTypeFromWaveFormatEx;
	FARPROC oMFInitVideoFormat;
	FARPROC oMFInitVideoFormat_RGB;
	FARPROC oMFInvokeCallback;
	FARPROC oMFJoinIoPort;
	FARPROC oMFJoinWorkQueue;
	FARPROC oMFLockDXGIDeviceManager;
	FARPROC oMFLockPlatform;
	FARPROC oMFLockSharedWorkQueue;
	FARPROC oMFLockWorkQueue;
	FARPROC oMFMapDX9FormatToDXGIFormat;
	FARPROC oMFMapDXGIFormatToDX9Format;
	FARPROC oMFPutWaitingWorkItem;
	FARPROC oMFPutWorkItem;
	FARPROC oMFPutWorkItem2;
	FARPROC oMFPutWorkItemEx;
	FARPROC oMFPutWorkItemEx2;
	FARPROC oMFRemovePeriodicCallback;
	FARPROC oMFResetDXGIDeviceManagerX;
	FARPROC oMFScheduleWorkItem;
	FARPROC oMFScheduleWorkItemEx;
	FARPROC oMFSerializeAttributesToStream;
	FARPROC oMFSerializeEvent;
	FARPROC oMFSerializeMediaTypeToStream;
	FARPROC oMFSerializePresentationDescriptor;
	FARPROC oMFShutdown;
	FARPROC oMFStartup;
	FARPROC oMFTEnumEx;
	FARPROC oMFTraceError;
	FARPROC oMFTraceFuncEnter;
	FARPROC oMFUnblockThread;
	FARPROC oMFUnjoinWorkQueue;
	FARPROC oMFUnlockDXGIDeviceManager;
	FARPROC oMFUnlockPlatform;
	FARPROC oMFUnlockWorkQueue;
	FARPROC oMFUnwrapMediaType;
	FARPROC oMFValidateMediaTypeSize;
	FARPROC oMFWrapMediaType;
	FARPROC oMFllMulDiv;
	FARPROC oPropVariantFromStream;
	FARPROC oPropVariantToStream;
	FARPROC oValidateWaveFormat;
} mfplat;

extern "C" {
	FARPROC PA = 0;
	int runASM();

	void fCopyPropVariant() { PA = mfplat.oCopyPropVariant; runASM(); }
	void fCreatePropVariant() { PA = mfplat.oCreatePropVariant; runASM(); }
	void fCreatePropertyStore() { PA = mfplat.oCreatePropertyStore; runASM(); }
	void fDestroyPropVariant() { PA = mfplat.oDestroyPropVariant; runASM(); }
	void fGetAMSubtypeFromD3DFormat() { PA = mfplat.oGetAMSubtypeFromD3DFormat; runASM(); }
	void fGetD3DFormatFromMFSubtype() { PA = mfplat.oGetD3DFormatFromMFSubtype; runASM(); }
	void fLFGetGlobalPool() { PA = mfplat.oLFGetGlobalPool; runASM(); }
	void fMFAddPeriodicCallback() { PA = mfplat.oMFAddPeriodicCallback; runASM(); }
	void fMFAllocateSerialWorkQueue() { PA = mfplat.oMFAllocateSerialWorkQueue; runASM(); }
	void fMFAllocateWorkQueue() { PA = mfplat.oMFAllocateWorkQueue; runASM(); }
	void fMFAllocateWorkQueueEx() { PA = mfplat.oMFAllocateWorkQueueEx; runASM(); }
	void fMFAppendCollection() { PA = mfplat.oMFAppendCollection; runASM(); }
	void fMFAverageTimePerFrameToFrameRate() { PA = mfplat.oMFAverageTimePerFrameToFrameRate; runASM(); }
	void fMFBeginCreateFile() { PA = mfplat.oMFBeginCreateFile; runASM(); }
	void fMFBlockThread() { PA = mfplat.oMFBlockThread; runASM(); }
	void fMFCalculateBitmapImageSize() { PA = mfplat.oMFCalculateBitmapImageSize; runASM(); }
	void fMFCalculateImageSize() { PA = mfplat.oMFCalculateImageSize; runASM(); }
	void fMFCancelCreateFile() { PA = mfplat.oMFCancelCreateFile; runASM(); }
	void fMFCancelWorkItem() { PA = mfplat.oMFCancelWorkItem; runASM(); }
	void fMFConvertColorInfoFromDXVA() { PA = mfplat.oMFConvertColorInfoFromDXVA; runASM(); }
	void fMFConvertColorInfoToDXVA() { PA = mfplat.oMFConvertColorInfoToDXVA; runASM(); }
	void fMFConvertFromFP16Array() { PA = mfplat.oMFConvertFromFP16Array; runASM(); }
	void fMFConvertToFP16Array() { PA = mfplat.oMFConvertToFP16Array; runASM(); }
	void fMFCopyImage() { PA = mfplat.oMFCopyImage; runASM(); }
	void fMFCreate2DMediaBuffer() { PA = mfplat.oMFCreate2DMediaBuffer; runASM(); }
	void fMFCreateAMMediaTypeFromMFMediaType() { PA = mfplat.oMFCreateAMMediaTypeFromMFMediaType; runASM(); }
	void fMFCreateAlignedMemoryBuffer() { PA = mfplat.oMFCreateAlignedMemoryBuffer; runASM(); }
	void fMFCreateAsyncResult() { PA = mfplat.oMFCreateAsyncResult; runASM(); }
	void fMFCreateAttributes() { PA = mfplat.oMFCreateAttributes; runASM(); }
	void fMFCreateAudioMediaType() { PA = mfplat.oMFCreateAudioMediaType; runASM(); }
	void fMFCreateCollection() { PA = mfplat.oMFCreateCollection; runASM(); }
	void fMFCreateDXGIDeviceManager() { PA = mfplat.oMFCreateDXGIDeviceManager; runASM(); }
	void fMFCreateDXGISurfaceBufferX() { PA = mfplat.oMFCreateDXGISurfaceBufferX; runASM(); }
	void fMFCreateDxvaSampleRendererX() { PA = mfplat.oMFCreateDxvaSampleRendererX; runASM(); }
	void fMFCreateEventQueue() { PA = mfplat.oMFCreateEventQueue; runASM(); }
	void fMFCreateFile() { PA = mfplat.oMFCreateFile; runASM(); }
	void fMFCreateFileFromHandle() { PA = mfplat.oMFCreateFileFromHandle; runASM(); }
	void fMFCreateLegacyMediaBufferOnMFMediaBuffer() { PA = mfplat.oMFCreateLegacyMediaBufferOnMFMediaBuffer; runASM(); }
	void fMFCreateMFByteStreamOnStream() { PA = mfplat.oMFCreateMFByteStreamOnStream; runASM(); }
	void fMFCreateMFVideoFormatFromMFMediaType() { PA = mfplat.oMFCreateMFVideoFormatFromMFMediaType; runASM(); }
	void fMFCreateMediaBufferFromMediaType() { PA = mfplat.oMFCreateMediaBufferFromMediaType; runASM(); }
	void fMFCreateMediaBufferWrapper() { PA = mfplat.oMFCreateMediaBufferWrapper; runASM(); }
	void fMFCreateMediaEvent() { PA = mfplat.oMFCreateMediaEvent; runASM(); }
	void fMFCreateMediaEventResult() { PA = mfplat.oMFCreateMediaEventResult; runASM(); }
	void fMFCreateMediaType() { PA = mfplat.oMFCreateMediaType; runASM(); }
	void fMFCreateMediaTypeFromRepresentation() { PA = mfplat.oMFCreateMediaTypeFromRepresentation; runASM(); }
	void fMFCreateMemoryBuffer() { PA = mfplat.oMFCreateMemoryBuffer; runASM(); }
	void fMFCreateMemoryStream() { PA = mfplat.oMFCreateMemoryStream; runASM(); }
	void fMFCreateNV12ToRGB32ConverterX() { PA = mfplat.oMFCreateNV12ToRGB32ConverterX; runASM(); }
	void fMFCreatePathFromURL() { PA = mfplat.oMFCreatePathFromURL; runASM(); }
	void fMFCreatePresentationDescriptor() { PA = mfplat.oMFCreatePresentationDescriptor; runASM(); }
	void fMFCreateRGB32ToNV12ConverterX() { PA = mfplat.oMFCreateRGB32ToNV12ConverterX; runASM(); }
	void fMFCreateSample() { PA = mfplat.oMFCreateSample; runASM(); }
	void fMFCreateSourceResolver() { PA = mfplat.oMFCreateSourceResolver; runASM(); }
	void fMFCreateSourceResolverInternal() { PA = mfplat.oMFCreateSourceResolverInternal; runASM(); }
	void fMFCreateStreamDescriptor() { PA = mfplat.oMFCreateStreamDescriptor; runASM(); }
	void fMFCreateSystemTimeSource() { PA = mfplat.oMFCreateSystemTimeSource; runASM(); }
	void fMFCreateTempFile() { PA = mfplat.oMFCreateTempFile; runASM(); }
	void fMFCreateTrackedSample() { PA = mfplat.oMFCreateTrackedSample; runASM(); }
	void fMFCreateURLFromPath() { PA = mfplat.oMFCreateURLFromPath; runASM(); }
	void fMFCreateVideoMediaType() { PA = mfplat.oMFCreateVideoMediaType; runASM(); }
	void fMFCreateVideoMediaTypeFromBitMapInfoHeader() { PA = mfplat.oMFCreateVideoMediaTypeFromBitMapInfoHeader; runASM(); }
	void fMFCreateVideoMediaTypeFromBitMapInfoHeaderEx() { PA = mfplat.oMFCreateVideoMediaTypeFromBitMapInfoHeaderEx; runASM(); }
	void fMFCreateVideoMediaTypeFromSubtype() { PA = mfplat.oMFCreateVideoMediaTypeFromSubtype; runASM(); }
	void fMFCreateVideoMediaTypeFromVideoInfoHeader() { PA = mfplat.oMFCreateVideoMediaTypeFromVideoInfoHeader; runASM(); }
	void fMFCreateVideoMediaTypeFromVideoInfoHeader2() { PA = mfplat.oMFCreateVideoMediaTypeFromVideoInfoHeader2; runASM(); }
	void fMFCreateVideoSampleAllocatorEx() { PA = mfplat.oMFCreateVideoSampleAllocatorEx; runASM(); }
	void fMFCreateWaveFormatExFromMFMediaType() { PA = mfplat.oMFCreateWaveFormatExFromMFMediaType; runASM(); }
	void fMFDeserializeAttributesFromStream() { PA = mfplat.oMFDeserializeAttributesFromStream; runASM(); }
	void fMFDeserializeEvent() { PA = mfplat.oMFDeserializeEvent; runASM(); }
	void fMFDeserializeMediaTypeFromStream() { PA = mfplat.oMFDeserializeMediaTypeFromStream; runASM(); }
	void fMFDeserializePresentationDescriptor() { PA = mfplat.oMFDeserializePresentationDescriptor; runASM(); }
	void fMFEndCreateFile() { PA = mfplat.oMFEndCreateFile; runASM(); }
	void fMFFrameRateToAverageTimePerFrame() { PA = mfplat.oMFFrameRateToAverageTimePerFrame; runASM(); }
	void fMFGetAttributesAsBlob() { PA = mfplat.oMFGetAttributesAsBlob; runASM(); }
	void fMFGetAttributesAsBlobSize() { PA = mfplat.oMFGetAttributesAsBlobSize; runASM(); }
	void fMFGetConfigurationDWORD() { PA = mfplat.oMFGetConfigurationDWORD; runASM(); }
	void fMFGetConfigurationPolicy() { PA = mfplat.oMFGetConfigurationPolicy; runASM(); }
	void fMFGetConfigurationStore() { PA = mfplat.oMFGetConfigurationStore; runASM(); }
	void fMFGetConfigurationString() { PA = mfplat.oMFGetConfigurationString; runASM(); }
	void fMFGetPlaneSize() { PA = mfplat.oMFGetPlaneSize; runASM(); }
	void fMFGetPlatform() { PA = mfplat.oMFGetPlatform; runASM(); }
	void fMFGetPrivateWorkqueues() { PA = mfplat.oMFGetPrivateWorkqueues; runASM(); }
	void fMFGetStrideForBitmapInfoHeader() { PA = mfplat.oMFGetStrideForBitmapInfoHeader; runASM(); }
	void fMFGetSupportedMimeTypes() { PA = mfplat.oMFGetSupportedMimeTypes; runASM(); }
	void fMFGetSupportedSchemes() { PA = mfplat.oMFGetSupportedSchemes; runASM(); }
	void fMFGetSystemTime() { PA = mfplat.oMFGetSystemTime; runASM(); }
	void fMFGetTimerPeriodicity() { PA = mfplat.oMFGetTimerPeriodicity; runASM(); }
	void fMFGetUncompressedVideoFormat() { PA = mfplat.oMFGetUncompressedVideoFormat; runASM(); }
	void fMFGetWorkQueueMMCSSTaskId() { PA = mfplat.oMFGetWorkQueueMMCSSTaskId; runASM(); }
	void fMFHeapAlloc() { PA = mfplat.oMFHeapAlloc; runASM(); }
	void fMFHeapFree() { PA = mfplat.oMFHeapFree; runASM(); }
	void fMFInitAMMediaTypeFromMFMediaType() { PA = mfplat.oMFInitAMMediaTypeFromMFMediaType; runASM(); }
	void fMFInitAttributesFromBlob() { PA = mfplat.oMFInitAttributesFromBlob; runASM(); }
	void fMFInitMediaTypeFromAMMediaType() { PA = mfplat.oMFInitMediaTypeFromAMMediaType; runASM(); }
	void fMFInitMediaTypeFromMFVideoFormat() { PA = mfplat.oMFInitMediaTypeFromMFVideoFormat; runASM(); }
	void fMFInitMediaTypeFromVideoInfoHeader() { PA = mfplat.oMFInitMediaTypeFromVideoInfoHeader; runASM(); }
	void fMFInitMediaTypeFromVideoInfoHeader2() { PA = mfplat.oMFInitMediaTypeFromVideoInfoHeader2; runASM(); }
	void fMFInitMediaTypeFromWaveFormatEx() { PA = mfplat.oMFInitMediaTypeFromWaveFormatEx; runASM(); }
	void fMFInitVideoFormat() { PA = mfplat.oMFInitVideoFormat; runASM(); }
	void fMFInitVideoFormat_RGB() { PA = mfplat.oMFInitVideoFormat_RGB; runASM(); }
	void fMFInvokeCallback() { PA = mfplat.oMFInvokeCallback; runASM(); }
	void fMFJoinIoPort() { PA = mfplat.oMFJoinIoPort; runASM(); }
	void fMFJoinWorkQueue() { PA = mfplat.oMFJoinWorkQueue; runASM(); }
	void fMFLockDXGIDeviceManager() { PA = mfplat.oMFLockDXGIDeviceManager; runASM(); }
	void fMFLockPlatform() { PA = mfplat.oMFLockPlatform; runASM(); }
	void fMFLockSharedWorkQueue() { PA = mfplat.oMFLockSharedWorkQueue; runASM(); }
	void fMFLockWorkQueue() { PA = mfplat.oMFLockWorkQueue; runASM(); }
	void fMFMapDX9FormatToDXGIFormat() { PA = mfplat.oMFMapDX9FormatToDXGIFormat; runASM(); }
	void fMFMapDXGIFormatToDX9Format() { PA = mfplat.oMFMapDXGIFormatToDX9Format; runASM(); }
	void fMFPutWaitingWorkItem() { PA = mfplat.oMFPutWaitingWorkItem; runASM(); }
	void fMFPutWorkItem() { PA = mfplat.oMFPutWorkItem; runASM(); }
	void fMFPutWorkItem2() { PA = mfplat.oMFPutWorkItem2; runASM(); }
	void fMFPutWorkItemEx() { PA = mfplat.oMFPutWorkItemEx; runASM(); }
	void fMFPutWorkItemEx2() { PA = mfplat.oMFPutWorkItemEx2; runASM(); }
	void fMFRemovePeriodicCallback() { PA = mfplat.oMFRemovePeriodicCallback; runASM(); }

	HRESULT __stdcall MFResetDXGIDeviceManager_X(IMFDXGIDeviceManager* pDeviceManager, IUnknown* pD3DDevice, UINT resetToken)
	{
		if (!pDeviceManager || !pD3DDevice)
			return E_INVALIDARG;

		HRESULT hr = pDeviceManager->ResetDevice(pD3DDevice, resetToken);
		if (hr == E_NOINTERFACE)
			hr = E_INVALIDARG;

		return hr;
	}

	void fMFScheduleWorkItem() { PA = mfplat.oMFScheduleWorkItem; runASM(); }
	void fMFScheduleWorkItemEx() { PA = mfplat.oMFScheduleWorkItemEx; runASM(); }
	void fMFSerializeAttributesToStream() { PA = mfplat.oMFSerializeAttributesToStream; runASM(); }
	void fMFSerializeEvent() { PA = mfplat.oMFSerializeEvent; runASM(); }
	void fMFSerializeMediaTypeToStream() { PA = mfplat.oMFSerializeMediaTypeToStream; runASM(); }
	void fMFSerializePresentationDescriptor() { PA = mfplat.oMFSerializePresentationDescriptor; runASM(); }
	void fMFShutdown() { PA = mfplat.oMFShutdown; runASM(); }

	HRESULT fMFStartup(ULONG Version, DWORD dwFlags)
	{
		return reinterpret_cast<HRESULT(__stdcall*)(ULONG, ULONG)>(mfplat.oMFStartup)(MF_VERSION, dwFlags);
	}

	void fMFTEnumEx() { PA = mfplat.oMFTEnumEx; runASM(); }
	void fMFTraceError() { PA = mfplat.oMFTraceError; runASM(); }
	void fMFTraceFuncEnter() { PA = mfplat.oMFTraceFuncEnter; runASM(); }
	void fMFUnblockThread() { PA = mfplat.oMFUnblockThread; runASM(); }
	void fMFUnjoinWorkQueue() { PA = mfplat.oMFUnjoinWorkQueue; runASM(); }
	void fMFUnlockDXGIDeviceManager() { PA = mfplat.oMFUnlockDXGIDeviceManager; runASM(); }
	void fMFUnlockPlatform() { PA = mfplat.oMFUnlockPlatform; runASM(); }
	void fMFUnlockWorkQueue() { PA = mfplat.oMFUnlockWorkQueue; runASM(); }
	void fMFUnwrapMediaType() { PA = mfplat.oMFUnwrapMediaType; runASM(); }
	void fMFValidateMediaTypeSize() { PA = mfplat.oMFValidateMediaTypeSize; runASM(); }
	void fMFWrapMediaType() { PA = mfplat.oMFWrapMediaType; runASM(); }
	void fMFllMulDiv() { PA = mfplat.oMFllMulDiv; runASM(); }
	void fPropVariantFromStream() { PA = mfplat.oPropVariantFromStream; runASM(); }
	void fPropVariantToStream() { PA = mfplat.oPropVariantToStream; runASM(); }
	void fValidateWaveFormat() { PA = mfplat.oValidateWaveFormat; runASM(); }
}

void setupFunctions() {
	mfplat.oCopyPropVariant = GetProcAddress(mfplat.dll, "CopyPropVariant");
	mfplat.oCreatePropVariant = GetProcAddress(mfplat.dll, "CreatePropVariant");
	mfplat.oCreatePropertyStore = GetProcAddress(mfplat.dll, "CreatePropertyStore");
	mfplat.oDestroyPropVariant = GetProcAddress(mfplat.dll, "DestroyPropVariant");
	mfplat.oGetAMSubtypeFromD3DFormat = GetProcAddress(mfplat.dll, "GetAMSubtypeFromD3DFormat");
	mfplat.oGetD3DFormatFromMFSubtype = GetProcAddress(mfplat.dll, "GetD3DFormatFromMFSubtype");
	mfplat.oLFGetGlobalPool = GetProcAddress(mfplat.dll, "LFGetGlobalPool");
	mfplat.oMFAddPeriodicCallback = GetProcAddress(mfplat.dll, "MFAddPeriodicCallback");
	mfplat.oMFAllocateSerialWorkQueue = GetProcAddress(mfplat.dll, "MFAllocateSerialWorkQueue");
	mfplat.oMFAllocateWorkQueue = GetProcAddress(mfplat.dll, "MFAllocateWorkQueue");
	mfplat.oMFAllocateWorkQueueEx = GetProcAddress(mfplat.dll, "MFAllocateWorkQueueEx");
	mfplat.oMFAppendCollection = GetProcAddress(mfplat.dll, "MFAppendCollection");
	mfplat.oMFAverageTimePerFrameToFrameRate = GetProcAddress(mfplat.dll, "MFAverageTimePerFrameToFrameRate");
	mfplat.oMFBeginCreateFile = GetProcAddress(mfplat.dll, "MFBeginCreateFile");
	mfplat.oMFBlockThread = GetProcAddress(mfplat.dll, "MFBlockThread");
	mfplat.oMFCalculateBitmapImageSize = GetProcAddress(mfplat.dll, "MFCalculateBitmapImageSize");
	mfplat.oMFCalculateImageSize = GetProcAddress(mfplat.dll, "MFCalculateImageSize");
	mfplat.oMFCancelCreateFile = GetProcAddress(mfplat.dll, "MFCancelCreateFile");
	mfplat.oMFCancelWorkItem = GetProcAddress(mfplat.dll, "MFCancelWorkItem");
	mfplat.oMFConvertColorInfoFromDXVA = GetProcAddress(mfplat.dll, "MFConvertColorInfoFromDXVA");
	mfplat.oMFConvertColorInfoToDXVA = GetProcAddress(mfplat.dll, "MFConvertColorInfoToDXVA");
	mfplat.oMFConvertFromFP16Array = GetProcAddress(mfplat.dll, "MFConvertFromFP16Array");
	mfplat.oMFConvertToFP16Array = GetProcAddress(mfplat.dll, "MFConvertToFP16Array");
	mfplat.oMFCopyImage = GetProcAddress(mfplat.dll, "MFCopyImage");
	mfplat.oMFCreate2DMediaBuffer = GetProcAddress(mfplat.dll, "MFCreate2DMediaBuffer");
	mfplat.oMFCreateAMMediaTypeFromMFMediaType = GetProcAddress(mfplat.dll, "MFCreateAMMediaTypeFromMFMediaType");
	mfplat.oMFCreateAlignedMemoryBuffer = GetProcAddress(mfplat.dll, "MFCreateAlignedMemoryBuffer");
	mfplat.oMFCreateAsyncResult = GetProcAddress(mfplat.dll, "MFCreateAsyncResult");
	mfplat.oMFCreateAttributes = GetProcAddress(mfplat.dll, "MFCreateAttributes");
	mfplat.oMFCreateAudioMediaType = GetProcAddress(mfplat.dll, "MFCreateAudioMediaType");
	mfplat.oMFCreateCollection = GetProcAddress(mfplat.dll, "MFCreateCollection");
	mfplat.oMFCreateDXGIDeviceManager = GetProcAddress(mfplat.dll, "MFCreateDXGIDeviceManager");
	mfplat.oMFCreateDXGISurfaceBufferX = GetProcAddress(mfplat.dll, "MFCreateDXGISurfaceBufferX");
	mfplat.oMFCreateDxvaSampleRendererX = GetProcAddress(mfplat.dll, "MFCreateDxvaSampleRendererX");
	mfplat.oMFCreateEventQueue = GetProcAddress(mfplat.dll, "MFCreateEventQueue");
	mfplat.oMFCreateFile = GetProcAddress(mfplat.dll, "MFCreateFile");
	mfplat.oMFCreateFileFromHandle = GetProcAddress(mfplat.dll, "MFCreateFileFromHandle");
	mfplat.oMFCreateLegacyMediaBufferOnMFMediaBuffer = GetProcAddress(mfplat.dll, "MFCreateLegacyMediaBufferOnMFMediaBuffer");
	mfplat.oMFCreateMFByteStreamOnStream = GetProcAddress(mfplat.dll, "MFCreateMFByteStreamOnStream");
	mfplat.oMFCreateMFVideoFormatFromMFMediaType = GetProcAddress(mfplat.dll, "MFCreateMFVideoFormatFromMFMediaType");
	mfplat.oMFCreateMediaBufferFromMediaType = GetProcAddress(mfplat.dll, "MFCreateMediaBufferFromMediaType");
	mfplat.oMFCreateMediaBufferWrapper = GetProcAddress(mfplat.dll, "MFCreateMediaBufferWrapper");
	mfplat.oMFCreateMediaEvent = GetProcAddress(mfplat.dll, "MFCreateMediaEvent");
	mfplat.oMFCreateMediaEventResult = GetProcAddress(mfplat.dll, "MFCreateMediaEventResult");
	mfplat.oMFCreateMediaType = GetProcAddress(mfplat.dll, "MFCreateMediaType");
	mfplat.oMFCreateMediaTypeFromRepresentation = GetProcAddress(mfplat.dll, "MFCreateMediaTypeFromRepresentation");
	mfplat.oMFCreateMemoryBuffer = GetProcAddress(mfplat.dll, "MFCreateMemoryBuffer");
	mfplat.oMFCreateMemoryStream = GetProcAddress(mfplat.dll, "MFCreateMemoryStream");
	mfplat.oMFCreateNV12ToRGB32ConverterX = GetProcAddress(mfplat.dll, "MFCreateNV12ToRGB32ConverterX");
	mfplat.oMFCreatePathFromURL = GetProcAddress(mfplat.dll, "MFCreatePathFromURL");
	mfplat.oMFCreatePresentationDescriptor = GetProcAddress(mfplat.dll, "MFCreatePresentationDescriptor");
	mfplat.oMFCreateRGB32ToNV12ConverterX = GetProcAddress(mfplat.dll, "MFCreateRGB32ToNV12ConverterX");
	mfplat.oMFCreateSample = GetProcAddress(mfplat.dll, "MFCreateSample");
	mfplat.oMFCreateSourceResolver = GetProcAddress(mfplat.dll, "MFCreateSourceResolver");
	mfplat.oMFCreateSourceResolverInternal = GetProcAddress(mfplat.dll, "MFCreateSourceResolverInternal");
	mfplat.oMFCreateStreamDescriptor = GetProcAddress(mfplat.dll, "MFCreateStreamDescriptor");
	mfplat.oMFCreateSystemTimeSource = GetProcAddress(mfplat.dll, "MFCreateSystemTimeSource");
	mfplat.oMFCreateTempFile = GetProcAddress(mfplat.dll, "MFCreateTempFile");
	mfplat.oMFCreateTrackedSample = GetProcAddress(mfplat.dll, "MFCreateTrackedSample");
	mfplat.oMFCreateURLFromPath = GetProcAddress(mfplat.dll, "MFCreateURLFromPath");
	mfplat.oMFCreateVideoMediaType = GetProcAddress(mfplat.dll, "MFCreateVideoMediaType");
	mfplat.oMFCreateVideoMediaTypeFromBitMapInfoHeader = GetProcAddress(mfplat.dll, "MFCreateVideoMediaTypeFromBitMapInfoHeader");
	mfplat.oMFCreateVideoMediaTypeFromBitMapInfoHeaderEx = GetProcAddress(mfplat.dll, "MFCreateVideoMediaTypeFromBitMapInfoHeaderEx");
	mfplat.oMFCreateVideoMediaTypeFromSubtype = GetProcAddress(mfplat.dll, "MFCreateVideoMediaTypeFromSubtype");
	mfplat.oMFCreateVideoMediaTypeFromVideoInfoHeader = GetProcAddress(mfplat.dll, "MFCreateVideoMediaTypeFromVideoInfoHeader");
	mfplat.oMFCreateVideoMediaTypeFromVideoInfoHeader2 = GetProcAddress(mfplat.dll, "MFCreateVideoMediaTypeFromVideoInfoHeader2");
	mfplat.oMFCreateVideoSampleAllocatorEx = GetProcAddress(mfplat.dll, "MFCreateVideoSampleAllocatorEx");
	mfplat.oMFCreateWaveFormatExFromMFMediaType = GetProcAddress(mfplat.dll, "MFCreateWaveFormatExFromMFMediaType");
	mfplat.oMFDeserializeAttributesFromStream = GetProcAddress(mfplat.dll, "MFDeserializeAttributesFromStream");
	mfplat.oMFDeserializeEvent = GetProcAddress(mfplat.dll, "MFDeserializeEvent");
	mfplat.oMFDeserializeMediaTypeFromStream = GetProcAddress(mfplat.dll, "MFDeserializeMediaTypeFromStream");
	mfplat.oMFDeserializePresentationDescriptor = GetProcAddress(mfplat.dll, "MFDeserializePresentationDescriptor");
	mfplat.oMFEndCreateFile = GetProcAddress(mfplat.dll, "MFEndCreateFile");
	mfplat.oMFFrameRateToAverageTimePerFrame = GetProcAddress(mfplat.dll, "MFFrameRateToAverageTimePerFrame");
	mfplat.oMFGetAttributesAsBlob = GetProcAddress(mfplat.dll, "MFGetAttributesAsBlob");
	mfplat.oMFGetAttributesAsBlobSize = GetProcAddress(mfplat.dll, "MFGetAttributesAsBlobSize");
	mfplat.oMFGetConfigurationDWORD = GetProcAddress(mfplat.dll, "MFGetConfigurationDWORD");
	mfplat.oMFGetConfigurationPolicy = GetProcAddress(mfplat.dll, "MFGetConfigurationPolicy");
	mfplat.oMFGetConfigurationStore = GetProcAddress(mfplat.dll, "MFGetConfigurationStore");
	mfplat.oMFGetConfigurationString = GetProcAddress(mfplat.dll, "MFGetConfigurationString");
	mfplat.oMFGetPlaneSize = GetProcAddress(mfplat.dll, "MFGetPlaneSize");
	mfplat.oMFGetPlatform = GetProcAddress(mfplat.dll, "MFGetPlatform");
	mfplat.oMFGetPrivateWorkqueues = GetProcAddress(mfplat.dll, "MFGetPrivateWorkqueues");
	mfplat.oMFGetStrideForBitmapInfoHeader = GetProcAddress(mfplat.dll, "MFGetStrideForBitmapInfoHeader");
	mfplat.oMFGetSupportedMimeTypes = GetProcAddress(mfplat.dll, "MFGetSupportedMimeTypes");
	mfplat.oMFGetSupportedSchemes = GetProcAddress(mfplat.dll, "MFGetSupportedSchemes");
	mfplat.oMFGetSystemTime = GetProcAddress(mfplat.dll, "MFGetSystemTime");
	mfplat.oMFGetTimerPeriodicity = GetProcAddress(mfplat.dll, "MFGetTimerPeriodicity");
	mfplat.oMFGetUncompressedVideoFormat = GetProcAddress(mfplat.dll, "MFGetUncompressedVideoFormat");
	mfplat.oMFGetWorkQueueMMCSSTaskId = GetProcAddress(mfplat.dll, "MFGetWorkQueueMMCSSTaskId");
	mfplat.oMFHeapAlloc = GetProcAddress(mfplat.dll, "MFHeapAlloc");
	mfplat.oMFHeapFree = GetProcAddress(mfplat.dll, "MFHeapFree");
	mfplat.oMFInitAMMediaTypeFromMFMediaType = GetProcAddress(mfplat.dll, "MFInitAMMediaTypeFromMFMediaType");
	mfplat.oMFInitAttributesFromBlob = GetProcAddress(mfplat.dll, "MFInitAttributesFromBlob");
	mfplat.oMFInitMediaTypeFromAMMediaType = GetProcAddress(mfplat.dll, "MFInitMediaTypeFromAMMediaType");
	mfplat.oMFInitMediaTypeFromMFVideoFormat = GetProcAddress(mfplat.dll, "MFInitMediaTypeFromMFVideoFormat");
	mfplat.oMFInitMediaTypeFromVideoInfoHeader = GetProcAddress(mfplat.dll, "MFInitMediaTypeFromVideoInfoHeader");
	mfplat.oMFInitMediaTypeFromVideoInfoHeader2 = GetProcAddress(mfplat.dll, "MFInitMediaTypeFromVideoInfoHeader2");
	mfplat.oMFInitMediaTypeFromWaveFormatEx = GetProcAddress(mfplat.dll, "MFInitMediaTypeFromWaveFormatEx");
	mfplat.oMFInitVideoFormat = GetProcAddress(mfplat.dll, "MFInitVideoFormat");
	mfplat.oMFInitVideoFormat_RGB = GetProcAddress(mfplat.dll, "MFInitVideoFormat_RGB");
	mfplat.oMFInvokeCallback = GetProcAddress(mfplat.dll, "MFInvokeCallback");
	mfplat.oMFJoinIoPort = GetProcAddress(mfplat.dll, "MFJoinIoPort");
	mfplat.oMFJoinWorkQueue = GetProcAddress(mfplat.dll, "MFJoinWorkQueue");
	mfplat.oMFLockDXGIDeviceManager = GetProcAddress(mfplat.dll, "MFLockDXGIDeviceManager");
	mfplat.oMFLockPlatform = GetProcAddress(mfplat.dll, "MFLockPlatform");
	mfplat.oMFLockSharedWorkQueue = GetProcAddress(mfplat.dll, "MFLockSharedWorkQueue");
	mfplat.oMFLockWorkQueue = GetProcAddress(mfplat.dll, "MFLockWorkQueue");
	mfplat.oMFMapDX9FormatToDXGIFormat = GetProcAddress(mfplat.dll, "MFMapDX9FormatToDXGIFormat");
	mfplat.oMFMapDXGIFormatToDX9Format = GetProcAddress(mfplat.dll, "MFMapDXGIFormatToDX9Format");
	mfplat.oMFPutWaitingWorkItem = GetProcAddress(mfplat.dll, "MFPutWaitingWorkItem");
	mfplat.oMFPutWorkItem = GetProcAddress(mfplat.dll, "MFPutWorkItem");
	mfplat.oMFPutWorkItem2 = GetProcAddress(mfplat.dll, "MFPutWorkItem2");
	mfplat.oMFPutWorkItemEx = GetProcAddress(mfplat.dll, "MFPutWorkItemEx");
	mfplat.oMFPutWorkItemEx2 = GetProcAddress(mfplat.dll, "MFPutWorkItemEx2");
	mfplat.oMFRemovePeriodicCallback = GetProcAddress(mfplat.dll, "MFRemovePeriodicCallback");
	mfplat.oMFResetDXGIDeviceManagerX = GetProcAddress(mfplat.dll, "MFResetDXGIDeviceManagerX");
	mfplat.oMFScheduleWorkItem = GetProcAddress(mfplat.dll, "MFScheduleWorkItem");
	mfplat.oMFScheduleWorkItemEx = GetProcAddress(mfplat.dll, "MFScheduleWorkItemEx");
	mfplat.oMFSerializeAttributesToStream = GetProcAddress(mfplat.dll, "MFSerializeAttributesToStream");
	mfplat.oMFSerializeEvent = GetProcAddress(mfplat.dll, "MFSerializeEvent");
	mfplat.oMFSerializeMediaTypeToStream = GetProcAddress(mfplat.dll, "MFSerializeMediaTypeToStream");
	mfplat.oMFSerializePresentationDescriptor = GetProcAddress(mfplat.dll, "MFSerializePresentationDescriptor");
	mfplat.oMFShutdown = GetProcAddress(mfplat.dll, "MFShutdown");
	mfplat.oMFStartup = GetProcAddress(mfplat.dll, "MFStartup");
	mfplat.oMFTEnumEx = GetProcAddress(mfplat.dll, "MFTEnumEx");
	mfplat.oMFTraceError = GetProcAddress(mfplat.dll, "MFTraceError");
	mfplat.oMFTraceFuncEnter = GetProcAddress(mfplat.dll, "MFTraceFuncEnter");
	mfplat.oMFUnblockThread = GetProcAddress(mfplat.dll, "MFUnblockThread");
	mfplat.oMFUnjoinWorkQueue = GetProcAddress(mfplat.dll, "MFUnjoinWorkQueue");
	mfplat.oMFUnlockDXGIDeviceManager = GetProcAddress(mfplat.dll, "MFUnlockDXGIDeviceManager");
	mfplat.oMFUnlockPlatform = GetProcAddress(mfplat.dll, "MFUnlockPlatform");
	mfplat.oMFUnlockWorkQueue = GetProcAddress(mfplat.dll, "MFUnlockWorkQueue");
	mfplat.oMFUnwrapMediaType = GetProcAddress(mfplat.dll, "MFUnwrapMediaType");
	mfplat.oMFValidateMediaTypeSize = GetProcAddress(mfplat.dll, "MFValidateMediaTypeSize");
	mfplat.oMFWrapMediaType = GetProcAddress(mfplat.dll, "MFWrapMediaType");
	mfplat.oMFllMulDiv = GetProcAddress(mfplat.dll, "MFllMulDiv");
	mfplat.oPropVariantFromStream = GetProcAddress(mfplat.dll, "PropVariantFromStream");
	mfplat.oPropVariantToStream = GetProcAddress(mfplat.dll, "PropVariantToStream");
	mfplat.oValidateWaveFormat = GetProcAddress(mfplat.dll, "ValidateWaveFormat");
}
#pragma endregion

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		char path[MAX_PATH];
		GetWindowsDirectoryA(path, sizeof(path));

		strcat_s(path, "\\System32\\mfplat.dll");
		mfplat.dll = LoadLibraryA(path);
		setupFunctions();

		break;
	case DLL_PROCESS_DETACH:
		FreeLibrary(mfplat.dll);
		break;
	}
	return 1;
}
