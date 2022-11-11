#pragma once

#include "../DXUtil.h"
#include "../_deps/function2/function2.hpp"

namespace Chen::CDX12 {
	class ResourceDeleteBatch {
	public:
		ResourceDeleteBatch() = default;
		ResourceDeleteBatch(const ResourceDeleteBatch&) = delete;
		ResourceDeleteBatch(ResourceDeleteBatch&&) noexcept = default;
		ResourceDeleteBatch& operator=(const ResourceDeleteBatch&) = delete;
		ResourceDeleteBatch& operator=(ResourceDeleteBatch&&) noexcept = default;
		~ResourceDeleteBatch();
		void Add(Microsoft::WRL::ComPtr<ID3D12Resource> resource);
		void AddCallback(fu2::unique_function<void()> callback);
		void Release();
	private:
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resources;
		std::vector<fu2::unique_function<void()>> callbacks;
	};
}
