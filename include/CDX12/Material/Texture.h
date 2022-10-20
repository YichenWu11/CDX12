#pragma once

#include "../DXUtil.h"

namespace Chen::CDX12 {
    enum class TextureDimension : uint8_t 
    {
        None,
        Tex1D,
        Tex2D,
        Tex3D,
        Cubemap,
        Tex2DArray,
    };

    struct Texture
    {
        // Unique material name for lookup.
        std::string Name;

        std::wstring Filename;

        Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;
        Microsoft::WRL::ComPtr<ID3D12Resource> UploadHeap = nullptr;

        TextureDimension dimension;

        Texture(TextureDimension _dimension = TextureDimension::Tex2D) : dimension(_dimension) {}

        D3D12_SHADER_RESOURCE_VIEW_DESC GetSrvDesc();
    };
}
