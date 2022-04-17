#include "ShaderManager.h"

namespace Devi
{
	void ShaderManager::addShader(std::shared_ptr<Shader> shader)
	{
		auto f = m_shaderMap.find(shader->GetName());

		if (f != m_shaderMap.end())
		{
			DEVI_ERROR("Shader for: " + shader->GetName() + " not inserted. It already exists.", __FILE__, __LINE__);
		}
		else
		{
			m_shaderMap.insert({ shader->GetName(), shader });
		}
		
	}

	void ShaderManager::addShader(const std::string& name, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath, std::optional<std::string> tessellationControlShaderFilePath, std::optional<std::string> tessellationEvaluationShaderFilePath)
	{
		auto shader = std::make_shared<Shader>(name, vertexShaderFilePath, fragmentShaderFilePath, tessellationControlShaderFilePath, tessellationEvaluationShaderFilePath);

		auto f = m_shaderMap.find(name);

		if (f != m_shaderMap.end())
		{
			DEVI_ERROR("Shader for: " + name + " not inserted. It already exists.", __FILE__, __LINE__);
		}
		else
		{
			m_shaderMap.insert({ name, shader });
		}
	}

	std::shared_ptr<Shader> ShaderManager::GetShader(const std::string& name)
	{
		auto shader = m_shaderMap.find(name);
		
		if (shader != m_shaderMap.end())
		{
			return shader->second;
		}
		
		else
		{
			DEVI_ERROR("Could not load the shader named: " + name, __FILE__, __LINE__);
		}

		return nullptr;
	}
}


