#include <CDX12/Resource/ResourceDeleteBatch.h>

using namespace Chen;

CDX12::ResourceDeleteBatch::~ResourceDeleteBatch() { Release(); }

void CDX12::ResourceDeleteBatch::Add(Microsoft::WRL::ComPtr<ID3D12Resource> resource) { resources.push_back(std::move(resource)); }

void CDX12::ResourceDeleteBatch::AddCallback(fu2::unique_function<void()> callback) { callbacks.push_back(std::move(callback)); }

void CDX12::ResourceDeleteBatch::Release() {
	resources.clear();
	for (auto& callback : callbacks)
		callback();
	callbacks.clear();
}
