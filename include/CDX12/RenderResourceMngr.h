#pragma once

#include "./Material/MaterialMngr.h"
#include "./Material/TextureMngr.h"
#include "./Geometry/MeshMngr.h"

namespace Chen::CDX12 {
	class RenderResourceMngr {
	public:
		static RenderResourceMngr& GetInstance() noexcept {
			static RenderResourceMngr instance;
			return instance;
		}

		void Init(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

		MaterialMngr* GetMatMngr()  { return matMngr; }
		TextureMngr*  GetTexMngr()  { return texMngr; }
		MeshMngr*     GetMeshMngr() { return meshMngr; }

		void Clear();
	private:
		RenderResourceMngr() = default;
		~RenderResourceMngr();

		bool isInit{ false };

		MaterialMngr* matMngr{ nullptr };
		TextureMngr*  texMngr{ nullptr };
		MeshMngr*    meshMngr{ nullptr };
	};
}
