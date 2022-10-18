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
}
