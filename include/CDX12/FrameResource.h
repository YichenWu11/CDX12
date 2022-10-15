#pragma once

#include "DXUtil.h"
#include "UploadBuffer.h"
#include "Math/MathHelper.h"
#include "CmdListHandle.h"
#include "GCmdList.h"

namespace Chen::CDX12 {
    class FrameResource
    {
    public:
    public:
        FrameResource(UINT64 cpuFence, ID3D12Fence* gpuFence) : cpuFence{ cpuFence }, gpuFence{ gpuFence } {}

        bool HaveResource(std::string_view name) const { return resourceMap.find(name) != resourceMap.end(); }

        template<typename T>
        FrameResource& RegisterResource(std::string name, T&& resource);

        FrameResource& UnregisterResource(std::string_view name);

        template<typename T>
        T& GetResource(std::string_view name);
        template<typename T>
        const T& GetResource(std::string_view name) const;

        CmdListHandle Command();
    private:
        friend class FrameResourceMngr;

        // cpu at frame [cpuFence] use the resources
        // when the frame complete (GPU instructions complete), gpuFence <- cpuFence
        void Signal(ID3D12CommandQueue* cmdQueue, UINT64 cpuFence);

        // at the cpu frame beginning, you should wait the frame complete
        // block cpu
        // run delay updator and unregister
        void BeginFrame(HANDLE sharedEventHandle);

        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CmdListAlloc;
        GCmdList CmdList; // CComPtr

        //std::unique_ptr<UploadBuffer<PassConstants>> PassCB = nullptr;

        ID3D12Fence* gpuFence;
        UINT64 cpuFence;
        std::map<std::string, std::any, std::less<>> resourceMap;
    };
}

#include "details/FrameResourceMngr.inl"