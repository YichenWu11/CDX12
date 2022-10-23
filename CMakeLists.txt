cmake_minimum_required(VERSION 3.5)

project(CDX12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILECOMMANDS ON)
add_definitions("-DUNICODE" "-D_UNICODE")

add_library(${PROJECT_NAME} 
    src/core/VarSizeAllocMngr.cpp
    src/core/DXUtil.cpp
    src/core/Device.cpp
    src/core/GeneralDesc.cpp
    src/core/DescriptorHeapMngr.cpp
    src/core/CmdQueue.cpp
    src/core/CmdListHandle.cpp
    src/core/GCmdList.cpp
    src/core/FrameResource.cpp
    src/core/FrameResourceMngr.cpp
    src/core/RenderResourceMngr.cpp

    src/core/Common/GameTimer.cpp
    src/core/Common/DX12App.cpp
    src/core/Common/Camera.cpp
    src/core/Common/Light.cpp
    
    src/core/Geometry/GeometryGenerator.cpp
    src/core/Geometry/MeshMngr.cpp

    src/core/Resource/Buffer.cpp
    
    src/core/Shader/GlobalSamplers.cpp
    src/core/Shader/Shader.cpp
    src/core/Shader/BasicShader.cpp
    src/core/Shader/PSOManager.cpp
    src/core/Shader/ShaderMngr.cpp

    src/core/Material/Texture.cpp
    src/core/Material/MaterialMngr.cpp
    src/core/Material/TextureMngr.cpp

    src/core/DescriptorHeap/DescriptorHeapAllocation.cpp
    src/core/DescriptorHeap/IDescriptorAllocator.cpp
    src/core/DescriptorHeap/DescriptorHeapAllocationMngr.cpp
    src/core/DescriptorHeap/CPUDescriptorHeap.cpp
    src/core/DescriptorHeap/GPUDescriptorHeap.cpp
    src/core/DescriptorHeap/DynamicSuballocMngr.cpp
    src/core/DescriptorHeap/DescriptorHeapWrapper.cpp

    src/core/Math/Quaternion.cpp
    src/core/Math/MathHelper.cpp
)

add_subdirectory(${CDX12_SOURCE_DIR}/DirectXTK12 ${CDX12_BINARY_DIR}/bin/CMake/DirectXTK12)
# add_subdirectory(${CMAKE_SOURCE_DIR}/DirectXTK12 ${CMAKE_BINARY_DIR}/bin/CMake/DirectXTK12)

add_library(Chen::CDX12 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC d3d12.lib
    PUBLIC dxgi.lib
    PUBLIC d3dcompiler.lib
    PUBLIC DirectXTK12
) 
