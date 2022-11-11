#pragma once

#include "DXUtil.h"

namespace Chen::CDX12 {
    // ID3DBlob is a CPU buffer wrapper
    // raw : Microsoft::WRL::ComPtr<ID3DBlob>
    // .   : simple API
    // ->  : raw API
    struct Blob : ComPtrHolder<ID3DBlob> {
        using ComPtrHolder<ID3DBlob>::ComPtrHolder;

        void Create(SIZE_T size);
        void Copy(const void* data, SIZE_T size);
        void Create(const void* data, SIZE_T size);
    };    
}