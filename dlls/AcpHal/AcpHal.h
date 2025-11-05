#pragma once
#include <inttypes.h>
#include "contexts.h"
#include "messages.h"
#include <cstdio>
#pragma once
typedef uint64_t APU_ADDRESS;

struct ApuHeapState {
/* 0x0000 */ public: uint32_t bytesFree;
/* 0x0004 */ public: uint32_t bytesAllocated;
/* 0x0008 */ public: uint32_t bytesLost;
/* 0x000c */ public: uint32_t maximumBlockSizeAvailable;
/* 0x0010 */ public: uint32_t allocationCount;
};
typedef struct APU_HEAP {
    void* Cached;
    void* NonCached;
    UINT32 CachedSize;
    UINT32 NonCachedSize;
} APU_HEAP;

static const UINT32 APU_ALLOC_CACHED = 0x00000001;
static const UINT32 APU_ALLOC_NONCACHED = 0x00000002;

#define ACPE_E_NOT_INITIALIZED     HRESULT(0x8AC80002)
#define ACPE_E_RESOURCE_IN_USE     HRESULT(0x8AC80010)
#define E_CRITICAL_SECTION_DEBUG_INFO_NOT_NULL 0x8ACA0001
struct SHAPE_CONTEXTS {
    UINT32 numSrcContexts;
    UINT32 numEqCompContexts;
    UINT32 numFiltVolContexts;
    UINT32 numDmaContexts;
    UINT32 numXmaContexts;
    UINT32 numPcmContexts;
    SHAPE_SRC_CONTEXT* srcContextArray;
    SHAPE_EQCOMP_CONTEXT* eqCompContextArray;
    SHAPE_FILTVOL_CONTEXT* filtVolContextArray;
    SHAPE_DMA_CONTEXT* dmaContextArray;
    SHAPE_XMA_CONTEXT* xmaContextArray;
    SHAPE_PCM_CONTEXT* pcmContextArray;
    APU_ADDRESS apuSrcContextArray;
    APU_ADDRESS apuEqCompContextArray;
    APU_ADDRESS apuFiltVolContextArray;
    APU_ADDRESS apuDmaContextArray;
    APU_ADDRESS apuXmaContextArray;
    APU_ADDRESS apuPcmContextArray;
};

typedef struct AcpHal_SHAPE_PCM_CONTEXT {
    UINT32 bufferStart : 32;
    UINT32 bufferLength : 21;
    UINT32 reserved0 : 11;
    UINT32 loopCount : 8;
    UINT32 reserved1 : 8;
    UINT32 full : 1;
    UINT32 reserved2 : 15;
    UINT32 readPointer : 21;
    UINT32 reserved3 : 11;
    UINT32 loopStartWritePointer : 21;
    UINT32 reserved4 : 11;
    UINT32 loopEnd : 21;
    UINT32 reserved5 : 11;
    UINT32 mode : 1;
    UINT32 reserved6 : 15;
    UINT32 format : 2;
    UINT32 reserved7 : 14;
    UINT32 reserved[ 1 ];
} AcpHal_SHAPE_PCM_CONTEXT;

typedef struct AcpHal_SHAPE_SRC_CONTEXT {
    UINT32 timestamp : 21;
    UINT32 blocksToSkip : 2;
    UINT32 internalSaturate : 1;
    UINT32 mixBufPeakMag : 4;
    UINT32 peakMag : 4;
    UINT32 samplingIncrement : 21;
    UINT32 reserved0 : 1;
    UINT32 cmd : 2;
    UINT32 mixBufPeakMag2 : 4;
    UINT32 peakMag2 : 4;
    UINT32 sampleCount : 32;
    UINT32 samplePointer : 25;
    UINT32 reserved1 : 7;
    UINT32 samplingIncrementTarget : 21;
    UINT32 reserved2 : 11;
    UINT32 reserved[ 3 ];
};

typedef struct AcpHal_SHAPE_EQCOMP_CONTEXT {
    UINT32 timestamp : 21;
    UINT32 reserved0 : 2;
    UINT32 internalSaturate : 1;
    UINT32 mixBufPeakMag : 4;
    UINT32 peakMag : 4;
    UINT32 eqAB0 : 24;
    UINT32 eqAB1_L : 8;
    UINT32 eqAB1_H : 16;
    UINT32 eqAB2_L : 16;
    UINT32 eqAB2_H : 8;
    UINT32 eqAA1 : 24;
    UINT32 eqAA2 : 24;
    UINT32 eqBB0_L : 8;
    UINT32 eqBB0_H : 16;
    UINT32 eqBB1_L : 16;
    UINT32 eqBB1_H : 8;
    UINT32 eqBB2 : 24;
    UINT32 eqBA1 : 24;
    UINT32 eqBA2_L : 8;
    UINT32 eqBA2_H : 16;
    UINT32 eqCB0_L : 16;
    UINT32 eqCB0_H : 8;
    UINT32 eqCB1 : 24;
    UINT32 eqCB2 : 24;
    UINT32 eqCA1_L : 8;
    UINT32 eqCA1_H : 16;
    UINT32 eqCA2_L : 16;
    UINT32 eqCA2_H : 8;
    UINT32 reserved1 : 24;
    UINT32 eqAInputDelay0 : 24;
    UINT32 reserved2 : 8;
    UINT32 eqAInputDelay1 : 24;
    UINT32 reserved3 : 8;
    UINT32 eqDelayElements2;
    UINT32 eqDelayElements3;
    UINT32 eqDelayElements4;
    UINT32 eqDelayElements5;
    UINT32 eqDelayElements6;
    UINT32 eqDelayElements7;
    UINT32 compInputLevel;
    UINT32 compGainReduction : 24;
    UINT32 reserved4 : 8;
    UINT32 compGain : 16;
    UINT32 reserved5 : 16;
    UINT32 eqAB0Target : 24;
    UINT32 eqAB1Target_L : 8;
    UINT32 eqAB1Target_H : 16;
    UINT32 eqAB2Target_L : 16;
    UINT32 eqAB2Target_H : 8;
    UINT32 eqAA1Target : 24;
    UINT32 eqAA2Target : 24;
    UINT32 eqBB0Target_L : 8;
    UINT32 eqBB0Target_H : 16;
    UINT32 eqBB1Target_L : 16;
    UINT32 eqBB1Target_H : 8;
    UINT32 eqBB2Target : 24;
    UINT32 eqBA1Target : 24;
    UINT32 eqBA2Target_L : 8;
    UINT32 eqBA2Target_H : 16;
    UINT32 eqCB0Target_L : 16;
    UINT32 eqCB0Target_H : 8;
    UINT32 eqCB1Target : 24;
    UINT32 eqCB2Target : 24;
    UINT32 eqCA1Target_L : 8;
    UINT32 eqCA1Target_H : 16;
    UINT32 eqCA2Target_L : 16;
    UINT32 eqCA2Target_H : 8;
    UINT32 reserved6 : 24;
    UINT32 compRelease : 24;
    UINT32 reserved7 : 2;
    UINT32 compExpand : 1;
    UINT32 compLogGain : 1;
    UINT32 compSidechainMode : 2;
    UINT32 compMode : 1;
    UINT32 compEnable : 1;
    UINT32 compThreshold : 24;
    UINT32 reserved8 : 8;
    UINT32 compAttack : 24;
    UINT32 reserved9 : 8;
    UINT32 compOneOverRatio : 16;
    UINT32 compGainTarget : 16;
} AcpHal_SHAPE_EQCOMP_CONTEXT;

typedef struct AcpHal_SHAPE_FILTVOL_CONTEXT {
    UINT32 timestamp : 21;
    UINT32 reserved0 : 2;
    UINT32 internalSaturate : 1;
    UINT32 mixBufPeakMag : 4;
    UINT32 peakMag : 4;
    UINT32 delay1 : 30;
    UINT32 headroom : 2;
    UINT32 delay2 : 30;
    UINT32 svfMode : 2;
    UINT32 gainTarget : 16;
    UINT32 gain : 16;
    UINT32 qRecip : 24;
    UINT32 reserved1 : 8;
    UINT32 qRecipTarget : 24;
    UINT32 reserved2 : 8;
    UINT32 fc : 24;
    UINT32 reserved3 : 8;
    UINT32 fcTarget : 24;
    UINT32 reserved4 : 8;
} AcpHal_SHAPE_FILTVOL_CONTEXT;

typedef struct AcpHal_SHAPE_DMA_CONTEXT {
    UINT32 timestamp : 21;
    UINT32 reserved0 : 3;
    UINT32 mixBufPeakMag : 4;
    UINT32 peakMag : 4;
    UINT32 readPointer : 5;
    UINT32 reserved1 : 3;
    UINT32 writePointer : 5;
    UINT32 reserved2 : 3;
    UINT32 full : 1;
    UINT32 reserved3 : 15;
    UINT32 reserved4 : 9;
    UINT32 address : 23;
    UINT32 numFrames : 5;
    UINT32 reserved5 : 3;
    UINT32 floatConvert : 1;
    UINT32 reserved6 : 7;
    UINT32 numChannels : 3;
    UINT32 reserved7 : 5;
    UINT32 channel : 3;
    UINT32 reserved8 : 5;
} AcpHal_SHAPE_DMA_CONTEXT;

typedef struct AcpHal_SHAPE_XMA_CONTEXT {
    UINT32 sizeRead0 : 12;
    UINT32 numLoops : 8;
    UINT32 validBuffer : 2;
    UINT32 sizeWrite : 5;
    UINT32 offsetWrite : 5;
    UINT32 sizeRead1 : 12;
    UINT32 loopSubframeEnd : 2;
    UINT32 reserved0 : 3;
    UINT32 loopSubframeSkip : 3;
    UINT32 numSubframesToDecode : 4;
    UINT32 numSubframesToSkip : 3;
    UINT32 sampleRate : 2;
    UINT32 numChannels : 1;
    UINT32 reserved1 : 1;
    UINT32 validWrite : 1;
    UINT32 offsetRead : 26;
    UINT32 errorStatus : 5;
    UINT32 errorSet : 1;
    UINT32 loopStartOffset : 26;
    UINT32 parserErrorStatus : 5;
    UINT32 parserErrorSet : 1;
    UINT32 loopEndOffset : 26;
    UINT32 packetMetaData : 5;
    UINT32 currentBuffer : 1;
    UINT32 ptrRead0;
    UINT32 ptrRead1;
    UINT32 ptrWrite;
    UINT32 ptrOverlapAdd;
    UINT32 writeBufferOffsetRead : 5;
    UINT32 reserved2 : 25;
    UINT32 stopWhenDone : 1;
    UINT32 interruptWhenDone : 1;
    UINT32 reserved[ 6 ];
} AcpHal_SHAPE_XMA_CONTEXT;

typedef struct AcpHal_SHAPE_CONTEXTS {
    UINT32 numSrcContexts;
    UINT32 numEqCompContexts;
    UINT32 numFiltVolContexts;
    UINT32 numDmaContexts;
    UINT32 numXmaContexts;
    UINT32 numPcmContexts;
    AcpHal_SHAPE_SRC_CONTEXT* srcContextArray;
    AcpHal_SHAPE_EQCOMP_CONTEXT* eqCompContextArray;
    AcpHal_SHAPE_FILTVOL_CONTEXT* filtVolContextArray;
    AcpHal_SHAPE_DMA_CONTEXT* dmaContextArray;
    AcpHal_SHAPE_XMA_CONTEXT* xmaContextArray;
    AcpHal_SHAPE_PCM_CONTEXT* pcmContextArray;
    APU_ADDRESS apuSrcContextArray;
    APU_ADDRESS apuEqCompContextArray;
    APU_ADDRESS apuFiltVolContextArray;
    APU_ADDRESS apuDmaContextArray;
    APU_ADDRESS apuXmaContextArray;
    APU_ADDRESS apuPcmContextArray;
} AcpHal_SHAPE_CONTEXTS;

enum ACP_COMMAND_TYPE
{
    ACP_COMMAND_TYPE_LOAD_SHAPE_FLOWGRAPH = 1,    
    ACP_COMMAND_TYPE_REGISTER_MESSAGE,            
    ACP_COMMAND_TYPE_UNREGISTER_MESSAGE,          
    ACP_COMMAND_TYPE_START_FLOWGRAPH,             
    ACP_COMMAND_TYPE_ENABLE_XMA_CONTEXT,          
    ACP_COMMAND_TYPE_ENABLE_XMA_CONTEXTS,         
    ACP_COMMAND_TYPE_DISABLE_XMA_CONTEXT,         
    ACP_COMMAND_TYPE_DISABLE_XMA_CONTEXTS,        
    ACP_COMMAND_TYPE_UPDATE_SRC_CONTEXT,          
    ACP_COMMAND_TYPE_UPDATE_EQCOMP_CONTEXT,       
    ACP_COMMAND_TYPE_UPDATE_FILTVOL_CONTEXT,      
    ACP_COMMAND_TYPE_UPDATE_DMA_CONTEXT,          
    ACP_COMMAND_TYPE_UPDATE_PCM_CONTEXT,          
    ACP_COMMAND_TYPE_UPDATE_XMA_CONTEXT,          
    ACP_COMMAND_TYPE_INCREMENT_DMA_WRITE_POINTER, 
    ACP_COMMAND_TYPE_INCREMENT_DMA_READ_POINTER,  
    ACP_COMMAND_TYPE_INCREMENT_PCM_WRITE_POINTER, 
    ACP_COMMAND_TYPE_INCREMENT_XMA_WRITE_BUFFER_OFFSET_READ,
    ACP_COMMAND_TYPE_UPDATE_XMA_READ_BUFFER,      
    ACP_COMMAND_TYPE_UPDATE_ALL_CONTEXTS,         
    ACP_COMMAND_TYPE_UPDATE_SRC_CONTEXTS,         
    ACP_COMMAND_TYPE_UPDATE_EQCOMP_CONTEXTS,      
    ACP_COMMAND_TYPE_UPDATE_FILTVOL_CONTEXTS,     
    ACP_COMMAND_TYPE_UPDATE_DMA_READ_CONTEXTS,    
    ACP_COMMAND_TYPE_UPDATE_DMA_WRITE_CONTEXTS,   
    ACP_COMMAND_TYPE_UPDATE_PCM_CONTEXTS,         
    ACP_COMMAND_TYPE_UPDATE_XMA_CONTEXTS,         

    ACP_COMMAND_TYPE_COUNT = ACP_COMMAND_TYPE_UPDATE_XMA_CONTEXTS 
};
struct ACP_MESSAGE
{
    UINT32 type;                // Message type
    UINT32 droppedMessageCount; // Count of dropped messages prior to this message
    UINT32 usec;                // time when this message is constructed
    union                       // Message data
    {
        ACP_MESSAGE_AUDIO_FRAME_START     audioFrameStart;
        ACP_MESSAGE_FLOWGRAPH_COMPLETED   flowgraphCompleted;
        ACP_MESSAGE_SHAPE_COMMAND_BLOCKED shapeCommandBlocked;
        ACP_MESSAGE_COMMAND_COMPLETED     commandCompleted;
        ACP_MESSAGE_FLOWGRAPH_TERMINATED  flowgraphTerminated;
        ACP_MESSAGE_ERROR                 error;
    };
};
class IAcpHal
{
public:
    IAcpHal() { printf("[IAcpHal] Constructed\n"); }
    virtual ~IAcpHal() { printf("[IAcpHal] Destructed\n"); }

    // Add virtual destructor to allow safe deletion
    virtual HRESULT __stdcall Connect(UINT32, UINT32) = 0;
    virtual HRESULT __stdcall Disconnect() = 0;
    virtual HRESULT __stdcall SubmitCommand(ACP_COMMAND_TYPE, UINT64, UINT32, const void*, APU_ADDRESS) = 0;
    virtual bool __stdcall PopMessage(ACP_MESSAGE* msg) = 0;
    virtual UINT32 __stdcall GetNumMessages() = 0;
    virtual void __stdcall Release() = 0;
};

class AcpHal : public IAcpHal {
    ULONG m_refCount = 1;

public:
    AcpHal() { printf("[AcpHal] Constructed\n"); }
    ~AcpHal() { printf("[AcpHal] Destructed\n"); }

    // COM reference tracking
    ULONG AddRef() { return ++m_refCount; }

    ULONG ReleaseRef() {
        ULONG ref = --m_refCount;
        if (ref == 0) {
            delete this;
            return 0;
        }
        return ref;
    }

    // IAcpHal methods
    HRESULT __stdcall Connect(UINT32, UINT32) override { printf("Connect()\n"); return S_OK; }
    HRESULT __stdcall Disconnect() override { printf("Disconnect()\n"); return S_OK; }
    HRESULT __stdcall SubmitCommand(ACP_COMMAND_TYPE, UINT64, UINT32, const void*, APU_ADDRESS) override {
        printf("SubmitCommand()\n");
        return S_OK;
    }
    bool __stdcall PopMessage(ACP_MESSAGE* msg) override {
        printf("PopMessage()\n");
        if (msg) ZeroMemory(msg, sizeof(*msg));
        return false;
    }
    UINT32 __stdcall GetNumMessages() override {
        printf("GetNumMessages()\n");
        return 0;
    }
    void __stdcall Release() override {
        printf("Release() called\n");
        ReleaseRef(); // Properly manages reference count
    }

};