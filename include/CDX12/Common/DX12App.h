#pragma once

// FIXME: Error --> "No Target Architecture"
//#include <winnt.h>
//#if defined(DEBUG) || defined(_DEBUG)
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#endif

#include "GameTimer.h"

#include "../DescripitorHeap/CPUDescriptorHeap.h"
#include "../DescripitorHeap/GPUDescriptorHeap.h"
#include "../DescripitorHeap/DescriptorHeapWrapper.h"

#include "../DXUtil.h"
#include "../CmdQueue.h"
#include "../DescriptorHeapMngr.h"
#include "../Device.h"
#include "../FrameResourceMngr.h"
#include "../Metalib.h"
#include "../GeneralDesc.h"

namespace Chen::CDX12 {
    class DX12App
    {
    protected:
        DX12App(HINSTANCE hInstance);
        DX12App(const DX12App& rhs) = delete;
        DX12App& operator=(const DX12App& rhs) = delete;
        virtual ~DX12App();
    public:
        static DX12App* GetAppInstance();
    
        HINSTANCE AppInst() const;
        HWND      MainWnd() const;
        float     AspectRatio() const;

        virtual int Run();
    
        virtual bool Initialize();
        virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

        void SetNumCpuCSU(uint32_t num) { numCpuCSU = num; }
        void SetNumCpuRTV(uint32_t num) { numCpuRTV = num; }
        void SetNumCpuDSV(uint32_t num) { numCpuDSV = num; }
        void SetNumGpuCSU_Static(uint32_t num) { numGpuCSU_static = num; }
        void SetNumGpuCSU_Dynamic(uint32_t num) { numGpuCSU_dynamic = num; }

    protected:
        virtual void CreateRtvAndDsvDescriptorHeaps();
        virtual void OnResize();
        virtual void Update(const GameTimer& gt)=0;
        virtual void Draw(const GameTimer& gt)=0;

        // Convenience overrides for handling mouse input.
        virtual void OnMouseDown(WPARAM btnState, int x, int y){ }
        virtual void OnMouseUp(WPARAM btnState, int x, int y)  { }
        virtual void OnMouseMove(WPARAM btnState, int x, int y){ }

    protected:

        bool InitMainWindow();       
        bool InitDirect3D();          
        void CreateCommandObjects(); 
        void CreateSwapChain();     

        ID3D12Resource* CurrentBackBuffer()const;  
        D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;  
        D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;      

        void CalculateFrameStats();

        void LogAdapters();
        void LogAdapterOutputs(IDXGIAdapter* adapter);
        void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

    protected:
        static DX12App* mApp;

        int gNumFrameResource = 3; // 3 frameResources

        HINSTANCE mhAppInst = nullptr; // application instance handle
        HWND      mhMainWnd = nullptr; // main window handle
        bool      mAppPaused = false;  // is the application paused?
        bool      mMinimized = false;  // is the application minimized?
        bool      mMaximized = false;  // is the application maximized?
        bool      mResizing = false;   // are the resize bars being dragged?
        bool      mFullscreenState = false;// fullscreen enabled

        GameTimer mTimer;

        Device mDevice;
        Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
        Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain; 

        CmdQueue mCmdQueue;
        GCmdList mCmdList;
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;

        std::unique_ptr<FrameResourceMngr> mFrameResourceMngr;

        static const int SwapChainBufferCount = 3;
        int mCurrBackBuffer = 0;
        Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
        Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;

        // DescriptorHeapMngr::GetInstance();  // this is the DescriptorHeap Manager For the App; 

        DescriptorHeapAllocation rtvCpuDH;
        DescriptorHeapAllocation dsvCpuDH;
        DescriptorHeapAllocation csuCpuDH;
        DescriptorHeapAllocation csuGpuDH;

        D3D12_VIEWPORT mScreenViewport;
        D3D12_RECT mScissorRect; 

        POINT mLastMousePos;

        std::wstring mMainWndCaption = L"CDX12App";
        D3D_DRIVER_TYPE md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
        DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
        DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
        int mClientWidth = 1000;
        int mClientHeight = 800;

        // Descriptor_Num
        uint32_t numCpuRTV = 3;
        uint32_t numCpuDSV = 1;
        uint32_t numCpuCSU = 168;
        uint32_t numGpuCSU_static = 168;
        uint32_t numGpuCSU_dynamic = 168;
    };
}