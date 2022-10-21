#pragma once

#include "ResourceUploadBatch.h"
#include "Texture.h"
#include "../DescripitorHeap/DescriptorHeapAllocation.h"

namespace Chen::CDX12 {
    class TextureMngr
    {
    public:
        enum class TexFileFormat : uint8_t
        {
            DDS = 0,
            WIC
        };

        TextureMngr(ID3D12Device* device, int size);
        ~TextureMngr();
        TextureMngr(const TextureMngr&)            = delete;
        TextureMngr& operator=(const TextureMngr&) = delete;

        size_t CreateTextureFromFile(
            ID3D12Device* device,
            ID3D12CommandQueue* cmdQueue,
            const std::wstring& path,
            const std::string& name,
            TexFileFormat format,
            TextureDimension dimension = TextureDimension::Tex2D);

        size_t GetTextureIndex(const std::string& name) const { 
            return (name2index.find(name) != name2index.end()) ? name2index.at(name) : InvalidIndex;
        }

        Texture* GetTexture(const std::string& name) {
            return (mTextures.find(name) != mTextures.end()) ? mTextures.at(name).get() : nullptr;
        }

        size_t GetTexNum() { return mTextures.size(); }

        std::vector<std::string>& GetTexNameList() { return nameList; }

    private:
        size_t InvalidIndex = -1;
        std::unordered_map<std::string, size_t> name2index;
        std::map<std::string, std::unique_ptr<Texture>> mTextures;
        std::vector<std::string> nameList;

        DirectX::ResourceUploadBatch resourceUpload;
        DescriptorHeapAllocation textureSrvAllocation;
    };
}
