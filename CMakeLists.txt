cmake_minimum_required(VERSION 3.5)

project(CDX12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILECOMMANDS ON)

add_library(${PROJECT_NAME} 
    src/core/VarSizeAllocMngr.cpp
    src/core/DXUtil.cpp
    src/core/Device.cpp
    src/core/GeneralDesc.cpp
    src/core/DescriptorHeapMngr.cpp
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
add_library(Chen::CDX12 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC d3d12.lib
    PUBLIC dxgi.lib
    PUBLIC d3dcompiler.lib
) 
