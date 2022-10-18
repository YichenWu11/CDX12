#pragma once

#include "../DXUtil.h"
#include "./BasicShader.h"

using Microsoft::WRL::ComPtr;

namespace Chen::CDX12 {
    class PSOManager {
    public:
        PSOManager(
            ID3D12Device* device,
            BasicShader* shader,
            DXGI_FORMAT mBackBufferFormat,
		    DXGI_FORMAT mDepthStencilFormat);

        void CreatePipelineState(
            std::string name,
            ID3D12Device* device,
            BasicShader* shader,
            UINT rtNum,
            DXGI_FORMAT mBackBufferFormat,
            DXGI_FORMAT mDepthStencilFormat);

        ID3D12PipelineState* GetPipelineState(const std::string& name) const {
            if (mPSOs.find(name) != mPSOs.end()) {
                return mPSOs.at(name).Get();
            }
            else {
                return nullptr;
            }
        }
    private:
        std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;
        D3D12_GRAPHICS_PIPELINE_STATE_DESC basePsoDesc;
    };
}
