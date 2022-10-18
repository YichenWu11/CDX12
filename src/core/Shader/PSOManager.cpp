#include <CDX12/Shader/PSOManager.h>
#include <CDX12/GeneralDesc.h>

using namespace Chen::CDX12;

PSOManager::PSOManager(
    ID3D12Device* device,
    BasicShader* shader,
    DXGI_FORMAT mBackBufferFormat,
    DXGI_FORMAT mDepthStencilFormat)
{
    basePsoDesc = 
        Desc::PSO::Basic(
            shader->RootSig(),
            shader->mInputLayout.data(),
            (UINT)shader->mInputLayout.size(),
            shader->vsShader.Get(),
            shader->psShader.Get(),
            mBackBufferFormat,
            mDepthStencilFormat);
    ThrowIfFailed(device->CreateGraphicsPipelineState(&basePsoDesc, IID_PPV_ARGS(&mPSOs["base"])));

    //
    // PSO for Transparent
    //

    D3D12_GRAPHICS_PIPELINE_STATE_DESC transparentPsoDesc = basePsoDesc;
    transparentPsoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
    transparentPsoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;

    D3D12_RENDER_TARGET_BLEND_DESC transparencyBlendDesc;
    transparencyBlendDesc.BlendEnable = true;
    transparencyBlendDesc.LogicOpEnable = false;

    transparencyBlendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
    transparencyBlendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
    transparencyBlendDesc.BlendOp = D3D12_BLEND_OP_ADD;

    transparencyBlendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
    transparencyBlendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
    transparencyBlendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;

    transparencyBlendDesc.LogicOp = D3D12_LOGIC_OP_NOOP;
    transparencyBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

    transparentPsoDesc.BlendState.RenderTarget[0] = transparencyBlendDesc;
    ThrowIfFailed(device->CreateGraphicsPipelineState(&transparentPsoDesc, IID_PPV_ARGS(&mPSOs["transparent"])));
}

void PSOManager::CreatePipelineState(
    std::string name,
    ID3D12Device* device,
    BasicShader* shader,
    UINT rtNum,
    DXGI_FORMAT mBackBufferFormat,
    DXGI_FORMAT mDepthStencilFormat)
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc
        = Desc::PSO::MRT(
            shader->RootSig(),
            shader->mInputLayout.data(),
            (UINT)shader->mInputLayout.size(),
            shader->vsShader.Get(),
            shader->psShader.Get(),
            rtNum,
            mBackBufferFormat,
            mDepthStencilFormat);
    psoDesc.RasterizerState = shader->rasterizerState;
    psoDesc.BlendState = shader->blendState;
    psoDesc.DepthStencilState = shader->depthStencilState;
    ThrowIfFailed(device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPSOs[name])));
}
