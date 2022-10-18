#include <CDX12/Shader/BasicShader.h>

using namespace Chen::CDX12;

BasicShader::BasicShader(
	std::span<std::pair<std::string, Property> const> properties,
	ID3D12Device* device)
	: Shader(properties, device) {}
BasicShader::BasicShader(
	std::span<std::pair<std::string, Property> const> properties,
	ComPtr<ID3D12RootSignature>&& rootSig)
	: Shader(properties, std::move(rootSig)) {}
