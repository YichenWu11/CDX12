#include <CDX12/RenderResourceMngr.h>

using namespace Chen::CDX12;

void RenderResourceMngr::Init(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList)
{
	assert(!isInit);

	matMngr = new MaterialMngr();
	texMngr = new TextureMngr(device);
	meshMngr = new MeshMngr(device, cmdList);

	isInit = true;
}

void RenderResourceMngr::Clear()
{
	isInit = false;

	delete matMngr;
	delete texMngr;
	delete meshMngr;

	matMngr = nullptr;
	texMngr = nullptr;
	meshMngr = nullptr;
}

RenderResourceMngr::~RenderResourceMngr()
{
	Clear();
}
