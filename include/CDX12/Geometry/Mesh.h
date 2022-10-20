#pragma once

#include "../DXUtil.h"

namespace Chen::CDX12 {
    struct SubmeshGeometry
    {
        UINT IndexCount = 0;
        UINT StartIndexLocation = 0;
        INT BaseVertexLocation = 0;

        DirectX::BoundingBox Bounds;
    };

    /* 一个 MeshGeometry 中可能含有多个 SubmeshGeometry，通过 map 来对应 */
    /* 几何图形辅助结构体 */

    struct MeshGeometry
    {
        std::string Name;

        Microsoft::WRL::ComPtr<ID3DBlob> VertexBufferCPU = nullptr;
        Microsoft::WRL::ComPtr<ID3DBlob> IndexBufferCPU = nullptr;

        // GPU End
        Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferGPU = nullptr;
        Microsoft::WRL::ComPtr<ID3D12Resource> IndexBufferGPU = nullptr;

        Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferUploader = nullptr;
        Microsoft::WRL::ComPtr<ID3D12Resource> IndexBufferUploader = nullptr;

        UINT VertexByteStride = 0;      // per vertex data size in bytes
        UINT VertexBufferByteSize = 0;  // vertex buffer total size in bytes
        DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT; // DXGI_FORMAT_R16_UINT / DXGI_FORMAT_R32_UINT
        UINT IndexBufferByteSize = 0;   // index buffer total size in bytes

        // 一个 MeshGeometry 结构体能够存储一组顶点/索引缓冲区中的多个几何体
        std::unordered_map<std::string, SubmeshGeometry> DrawArgs;

        D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const
        {
            D3D12_VERTEX_BUFFER_VIEW vbv;  // 返回一个顶点缓冲区描述符
            vbv.BufferLocation = VertexBufferGPU->GetGPUVirtualAddress();
            vbv.StrideInBytes = VertexByteStride;    // 类似步长
            vbv.SizeInBytes = VertexBufferByteSize;  // 类似总长

            return vbv;
        }

        D3D12_INDEX_BUFFER_VIEW IndexBufferView()const
        {
            D3D12_INDEX_BUFFER_VIEW ibv;  // 返回一个索引缓冲区描述符
            ibv.BufferLocation = IndexBufferGPU->GetGPUVirtualAddress();
            ibv.Format = IndexFormat;              // 索引的格式（必须表示为 DXGI_FORMAT_R16_UINT）
            ibv.SizeInBytes = IndexBufferByteSize; // 待创建视图的索引缓冲区大小

            return ibv;
        }

        void DisposeUploader()
        {
            VertexBufferUploader = nullptr;
            IndexBufferUploader  = nullptr;
        }
    };
}