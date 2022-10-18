#pragma once

#include "Shader.h"

using Microsoft::WRL::ComPtr;

namespace Chen::CDX12 {
    class RasterShader : public Shader {
    public:
        ComPtr<ID3DBlob> vsShader = nullptr;
        ComPtr<ID3DBlob> psShader = nullptr;
        ComPtr<ID3DBlob> hsShader = nullptr;
        ComPtr<ID3DBlob> dsShader = nullptr;
        D3D12_RASTERIZER_DESC rasterizeState;
        D3D12_DEPTH_STENCIL_DESC depthStencilState;
        D3D12_BLEND_DESC blendState;
        D3D12_INPUT_ELEMENT_DESC mInputLayout;
        RasterShader(
            std::span<std::pair<std::string, Property> const> properties,
            ID3D12Device* device);
        RasterShader(
            std::span<std::pair<std::string, Property> const> properties,
            ComPtr<ID3D12RootSignature>&& rootSig);
    };
}
