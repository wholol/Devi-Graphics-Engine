#pragma once
#include <unordered_map>
#include <memory>
#include "IDrawable.h"
#include "Shader.h"

namespace Devi
{
	class ShaderManager
	{

	public:
		void addShader(std::shared_ptr<Shader> shader);
		void addShader(
			const std::string& name, const std::string& vertexShaderFilePath, 
			const std::string& fragmentShaderFilePath,
			std::optional<std::string> tessellationControlShaderFilePath = {},
			std::optional<std::string> tessellationEvaluationShaderFilePath = {});

		std::shared_ptr<Shader> GetShader(const std::string& name);

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaderMap;
	};
}
