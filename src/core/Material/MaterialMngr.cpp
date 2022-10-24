#include <CDX12/Material/MaterialMngr.h>

using namespace Chen::CDX12;

const BasicMaterial* MaterialMngr::GetMaterial(const std::string &name) const
{
    if (mMaterials.find(name) != mMaterials.end())
        return mMaterials.at(name).get();
    else
        return nullptr;
}

void MaterialMngr::CreateMaterial(
    const std::string& name,
    int DiffuseSrvHeapIndex,
    DirectX::XMFLOAT4 DiffuseAlbedo,
    DirectX::XMFLOAT3 FresnelR0,
    float Roughness,
    int NormalSrvHeapIndex)
{
    auto mat = std::make_unique<BasicMaterial>();
	mat->Name = name;
	mat->MatIndex = mMaterials.size();
	mat->DiffuseSrvHeapIndex = DiffuseSrvHeapIndex;
	mat->NormalSrvHeapIndex = NormalSrvHeapIndex;
	mat->DiffuseAlbedo = DiffuseAlbedo;
	mat->FresnelR0 = FresnelR0;
	mat->Roughness = Roughness;

    nameList.push_back(name);

	mMaterials.try_emplace(name, std::move(mat));
}
