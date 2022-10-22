#pragma once

#include "BasicShader.h"

namespace Chen::CDX12 {
	class ShaderMngr
	{
	public:
		ShaderMngr(ID3D12Device* device) : device(device) {}
		~ShaderMngr();
		ShaderMngr(const ShaderMngr&) = delete;
		ShaderMngr& operator=(const ShaderMngr&) = delete;

		std::vector<std::string>& GetShaderNameList() { return nameList; }

		size_t GetShaderNum() { return mShaders.size(); }

		void CreateShader(
			std::string& name,
			std::span<std::pair<std::string, Shader::Property> const> properties,
			const wchar_t* vsPath,
			const wchar_t* psPath,
			const wchar_t* hsPath = nullptr,
			const wchar_t* dsPath = nullptr,
			const std::vector<D3D_SHADER_MACRO> shaderDefines = std::vector<D3D_SHADER_MACRO>());

		BasicShader* GetShader(std::string name) 
		{
			return (mShaders.find(name) != mShaders.end()) ? mShaders.at(name).get() : nullptr;
		}

	private:
		ID3D12Device* device;
		std::unordered_map<std::string, std::unique_ptr<BasicShader>> mShaders;
		std::vector<std::string> nameList;
	};
}
