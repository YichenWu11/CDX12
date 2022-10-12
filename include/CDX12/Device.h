#pragma once

#include "DXUtil.h"

namespace Chen::CDX12 {
    // raw : Microsoft::WRL::ComPtr<ID3D12Device>
    // .   : simple API
    // ->  : raw API
	struct Device : ComPtrHolder<ID3D12Device> {
		using ComPtrHolder<ID3D12Device>::ComPtrHolder;

        void CreateCommittedResource(
            D3D12_HEAP_TYPE heap_type,
            SIZE_T size,
            ID3D12Resource** resources);

        void CreateDescriptorHeap(UINT size, D3D12_DESCRIPTOR_HEAP_TYPE type,
            ID3D12DescriptorHeap** pHeap);

        ComPtr<ID3D12RootSignature> CreateRootSignature(const D3D12_ROOT_SIGNATURE_DESC& desc);
    };
}
