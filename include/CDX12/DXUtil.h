#pragma once

#include "_deps/d3dx12.h"
#include "dxcapi.h"

#include <d3dcompiler.h>
#include <string_view>
#include <wrl.h>

#include <string>

#include <cassert>

#include <DirectXMath.h>

namespace Chen::CDX12 {
    inline std::wstring AnsiToWString(const std::string& str)
    {
        WCHAR buffer[512];
        MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
        return std::wstring(buffer);
    }

    /*
    #if defined(_DEBUG)
        #ifndef Assert
        #define Assert(x, description)                                  \
        {                                                               \
            static bool ignoreAssert = false;                           \
            if(!ignoreAssert && !(x))                                   \
            {                                                           \
                Debug::AssertResult result = Debug::ShowAssertDialog(   \
                (L#x), description, AnsiToWString(__FILE__), __LINE__); \
            if(result == Debug::AssertIgnore)                           \
            {                                                           \
                ignoreAssert = true;                                    \
            }                                                           \
                        else if(result == Debug::AssertBreak)           \
            {                                                           \
                __debugbreak();                                         \
            }                                                           \
            }                                                           \
        }
        #endif
    #else
        #ifndef Assert
        #define Assert(x, description) 
        #endif
    #endif 		
        */

    class DXUtil
    {
    public:

        static bool IsKeyDown(int vkeyCode);

        static std::string ToString(HRESULT hr);

        static UINT CalcConstantBufferByteSize(UINT byteSize)
        {
            // Constant buffers must be a multiple of the minimum hardware
            // allocation size (usually 256 bytes).  So round up to nearest
            // multiple of 256.  We do this by adding 255 and then masking off
            // the lower 2 bytes which store all bits < 256.
            // Example: Suppose byteSize = 300.
            // (300 + 255) & ~255
            // 555 & ~255
            // 0x022B & ~0x00ff
            // 0x022B & 0xff00
            // 0x0200
            // 512
            return (byteSize + 255) & ~255;
        }

        static Microsoft::WRL::ComPtr<ID3DBlob> LoadBinary(const std::wstring& filename);

        static Microsoft::WRL::ComPtr<ID3D12Resource> CreateDefaultBuffer(
            ID3D12Device* device,
            ID3D12GraphicsCommandList* cmdList,
            const void* initData,
            UINT64 byteSize,
            Microsoft::WRL::ComPtr<ID3D12Resource>& uploadBuffer);

        // 可以把 ID3DBlob 理解成一块单纯的内存区域，类似 std::span
        static Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(
            const std::wstring& filename,
            const D3D_SHADER_MACRO* defines,
            const std::string& entrypoint,
            const std::string& target);
    };

    class DxException
    {
    public:
        DxException() = default;
        DxException(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber);

        std::wstring ToString()const;

        HRESULT ErrorCode = S_OK;
        std::wstring FunctionName;
        std::wstring Filename;
        int LineNumber = -1;
    };

    struct Light
    {
        DirectX::XMFLOAT3 Strength = { 0.5f, 0.5f, 0.5f };
        float FalloffStart = 1.0f;                          // point/spot light only
        DirectX::XMFLOAT3 Direction = { 0.0f, -1.0f, 0.0f };// directional/spot light only
        float FalloffEnd = 10.0f;                           // point/spot light only
        DirectX::XMFLOAT3 Position = { 0.0f, 0.0f, 0.0f };  // point/spot light only
        float SpotPower = 64.0f;                            // spot light only
    };

    #define MaxLights 16

    struct Texture
    {
        // Unique material name for lookup.
        std::string Name;

        std::wstring Filename;

        Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;
        Microsoft::WRL::ComPtr<ID3D12Resource> UploadHeap = nullptr;
    };
}

#ifndef ThrowIfFailed
#define ThrowIfFailed(x)                                              \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    std::wstring wfn = AnsiToWString(__FILE__);                       \
    if(FAILED(hr__)) { throw DxException(hr__, L#x, wfn, __LINE__); } \
}
#endif

#ifndef ReleaseCom
#define ReleaseCom(x) { if(x){ x->Release(); x = 0; } }
#endif
