#pragma once

#include "Texture.h"
#include "../DescripitorHeap/DescriptorHeapAllocation.h"

namespace Chen::CDX12 {
    class TextureMngr
    {
    public:
        TextureMngr(int size = 30);
        ~TextureMngr();
        TextureMngr(const TextureMngr&)            = delete;
        TextureMngr& operator=(const TextureMngr&) = delete;

        size_t CreateDDSTextureFromFile(
            ID3D12Device* device,
            ID3D12GraphicsCommandList* cmdList,
            const std::wstring& path, 
            const std::string& name,
            TextureDimension dimension = TextureDimension::Tex2D);

        size_t GetTextureIndex(const std::string& name) const { 
            return (name2index.find(name) != name2index.end()) ? name2index.at(name) : InvalidIndex;
        }

        Texture* GetTexture(const std::string& name) {
            return (mTextures.find(name) != mTextures.end()) ? mTextures.at(name).get() : nullptr;
        }

    private:
        size_t InvalidIndex = -1;
        std::unordered_map<std::string, size_t> name2index;
        std::map<std::string, std::unique_ptr<Texture>> mTextures;
    };
}
