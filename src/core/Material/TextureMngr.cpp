#include <CDX12/Material/TextureMngr.h>
#include <CDX12/Common/DDSTextureLoader.h>
#include <CDX12/DescriptorHeapMngr.h>

using namespace Chen::CDX12;

TextureMngr::TextureMngr(int size)
{
}


TextureMngr::~TextureMngr()
{
}

// return the index of the texture
size_t TextureMngr::CreateDDSTextureFromFile(
    ID3D12Device* device,
    ID3D12GraphicsCommandList* cmdList,
    const std::wstring& path, 
    const std::string& name, 
    TextureDimension dimension)
{
    if (name2index.find(name) != name2index.end()) return InvalidIndex;  // name_only
    auto tex = std::make_unique<Texture>(dimension);
    tex->Filename = path;
    tex->Name = name;
    ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(device,
        cmdList, tex->Filename.c_str(),
        tex->Resource, tex->UploadHeap));
    mTextures[tex->Name] = std::move(tex);
    name2index[tex->Name] = mTextures.size();

    // TODO: Whether to create the SRV of the texture directly here

    return name2index[tex->Name];
}
