#pragma once

#include "CDX12/DescripitorHeap/DescriptorAllocatonMngr.h"
#include "IDescriptorAllocator.h"
#include "../VarSizeAllocMngr.h"

#include <d3d12.h>
#include <mutex>

using namespace Chen::CDX12;

namespace Chen::CDX12 {
    /*
        Every allocation that the class creates is represented by an instance of DescriptorHeapAllocation class. 
        The list of free descriptors is managed by m_FreeBlocksManager member
    */
    class DescriptorHeapAllocationMngr {
    public:
        // Creates a new D3D12 descriptor heap
        DescriptorHeapAllocationMngr(
            ID3D12Device*                     pDevice,
            IDescriptorAllocator*             pParentAllocator,
            size_t                            ThisManagerId,
            const D3D12_DESCRIPTOR_HEAP_DESC& HeapDesc
        );

        // Uses subrange of descriptors in the existing D3D12 descriptor heap
        // that starts at offset FirstDescriptor and uses NumDescriptors descriptors
        DescriptorHeapAllocationMngr(
            ID3D12Device*         pDevice,
            IDescriptorAllocator* pParentAllocator,
            size_t                ThisManagerId,
            ID3D12DescriptorHeap* pd3d12Descriptor,
            uint32_t              FirstDescriptor,
            uint32_t              NumDescriptors
        );

        // Move constructor
        DescriptorHeapAllocationMngr(DescriptorHeapAllocationMngr&& rhs);

        DescriptorHeapAllocationMngr& operator=(DescriptorHeapAllocationMngr&& rhs) = delete;
        DescriptorHeapAllocationMngr(const DescriptorHeapAllocationMngr&) = delete;
        DescriptorHeapAllocationMngr& operator=(const DescriptorHeapAllocationMngr&) = delete;

        ~DescriptorHeapAllocationMngr();

        // Allocates Count descriptors
        DescriptorHeapAllocation Allocate(uint32_t Count);

        // Releases descriptor heap allocation. Note
        // that the allocation is not released immediately, but
        // added to the release queue in the allocations manager
        void Free(DescriptorHeapAllocation&& Allocation); 

        // Releases all stale allocation
        void ReleaseStaleAllocations(uint64_t NumCompletedFrames);

    private:
        
    };
}
