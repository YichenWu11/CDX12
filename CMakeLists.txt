cmake_minimum_required(VERSION 3.5)

project(CDX12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} 
    src/core/VarSizeAllocMngr.cpp
    src/core/DXUtil.cpp
    src/core/DescriptorHeap/DescriptorAllocation.cpp
    src/core/DescriptorHeap/IDescriptorAllocator.cpp
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
