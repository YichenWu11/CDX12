#include <CDX12/Blob.h>

using namespace Chen;

void CDX12::Blob::Create(SIZE_T size) {
    ThrowIfFailed(D3DCreateBlob(size, &raw));
}

void CDX12::Blob::Copy(const void* data, SIZE_T size) {
    CopyMemory(raw->GetBufferPointer(), data, size);
}

void CDX12::Blob::Create(const void* data, SIZE_T size) {
    Create(size);
    Copy(data, size);
}