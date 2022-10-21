#pragma once

#include "Mesh.h"

namespace Chen::CDX12 {

    // vertex
    struct Vertex
    {
        DirectX::XMFLOAT3 Pos;
        DirectX::XMFLOAT3 Normal;
        DirectX::XMFLOAT2 TexC;
        DirectX::XMFLOAT3 TangentU;
    };

    class MeshMngr 
    {
    public:
        enum class FileFormat : uint8_t
        {
            txt = 0,
        };

        MeshMngr(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);
        ~MeshMngr() = default;
        MeshMngr(const MeshMngr&) = delete;
        MeshMngr& operator=(const MeshMngr&) = delete;

        MeshGeometry* GetMeshGeo(const std::string& name) {
            return (mGeometries.find(name) != mGeometries.end()) ? mGeometries.at(name).get() : nullptr;
        }

        void BuildBasicGeo();

        void BuildTXTModelGeometryFromFile(
            const char* path, 
            const char* geoName, 
            const char* subName, 
            bool        is_normal, 
            bool        is_uv);

    private:
        ID3D12Device* device;
        ID3D12GraphicsCommandList* cmdList;
        std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
    };
}
