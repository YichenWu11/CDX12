#pragma once

#include "IDescriptorAllocator.h"
#include "GPUDescriptorHeap.h"

namespace Chen::CDX12 {
    // The class facilitates allocation of dynamic descriptor handles. It requests a chunk of heap
    // from the master GPU descriptor heap and then performs linear suballocation within the chunk
    // At the end of the frame all allocations are disposed.

    //     static and mutable handles     ||                 dynamic space
    //                                    ||    chunk 0                 chunk 2
    //  |                                 ||  | X X X O |             | O O O O |           || GPU Descriptor Heap
    //                                        |                       |
    //                                        m_Suballocations[0]     m_Suballocations[1]
    //
	class DynamicSuballocMngr final : public IDescriptorAllocator {
    public:
        DynamicSuballocMngr(
            GPUDescriptorHeap* ParentGPUHeap,
            uint32_t           DynamicChunkSize,
            std::string        ManagerName) noexcept;

        DynamicSuballocMngr            (const DynamicSuballocMngr&) = delete;
        DynamicSuballocMngr            (DynamicSuballocMngr&&)      = delete;
        DynamicSuballocMngr& operator= (const DynamicSuballocMngr&) = delete;
        DynamicSuballocMngr& operator= (DynamicSuballocMngr&&)      = delete;

        ~DynamicSuballocMngr();

        virtual DescriptorHeapAllocation Allocate(uint32_t count) override final;
        virtual void                     Free(DescriptorHeapAllocation&& allocation) noexcept override final {
            // Do nothing. Dynamic allocations are not disposed individually, but as whole chunks
            // at the end of the frame by ReleaseAllocations()
            allocation.Reset();
        }

        void ReleaseAllocations();

        virtual uint32_t GetDescriptorSize() const noexcept override final { return m_ParentGPUHeap->GetDescriptorSize(); }

        size_t GetSuballocationCount() const noexcept { return m_Suballocations.size(); }

    private:
        // Parent GPU descriptor heap that is used to allocate chunks
        GPUDescriptorHeap* m_ParentGPUHeap;
        std::string        m_ManagerName;

        // List of chunks allocated from the master GPU descriptor heap. All chunks are disposed at the end
        // of the frame
        std::vector<DescriptorHeapAllocation> m_Suballocations;

        uint32_t m_CurrentSuballocationOffset = 0;
        uint32_t m_DynamicChunkSize           = 0;

        uint32_t m_CurrDescriptorCount         = 0;
        uint32_t m_PeakDescriptorCount         = 0;
        uint32_t m_CurrSuballocationsTotalSize = 0;
        uint32_t m_PeakSuballocationsTotalSize = 0;
    };
}
