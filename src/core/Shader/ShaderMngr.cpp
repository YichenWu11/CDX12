#include <CDX12/Shader/ShaderMngr.h>

using namespace Chen::CDX12;

void ShaderMngr::CreateShader(
	std::string& name,
	std::span<std::pair<std::string, Shader::Property> const> properties,
	const wchar_t* vsPath,
	const wchar_t* psPath,
	const wchar_t* hsPath,
	const wchar_t* dsPath,
	const std::vector<D3D_SHADER_MACRO> shaderDefines)
{
	auto shader = std::make_unique<BasicShader>(properties, device);
	shader->SetVsShader(vsPath, shaderDefines);
	shader->SetPsShader(psPath, shaderDefines);
	shader->SetHsShader(hsPath, shaderDefines);
	shader->SetDsShader(dsPath, shaderDefines);

	mShaders[name] = std::move(shader);
	nameList.push_back(name);
}

ShaderMngr::~ShaderMngr() {}
