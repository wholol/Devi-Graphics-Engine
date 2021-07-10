#pragma once
#include <string>
#include <any>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Log.h"
#include "NotImplementedException.h"

namespace Devi
{
	/**
	* The data type for the uniforms used by the shader. Add new data type here if needed.
	**/
	enum class UniformDataType
	{
		FLOAT,
		DOUBLE,
		INT,
		BOOL,
		MAT2,
		MAT3,
		MAT4,
		VEC2,
		VEC3,
		VEC4,
	};

	/**
	* Shader class. Responsible for compiling shaders at startup and binding them whenever needed with uniforms provided.
	**/
	class Shader
	{

	public:
		Shader() = delete;
		Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void Bind();
		void UnBind();
		void SetUniform(const std::string& uniformName, const std::any& uniformValue, UniformDataType uniformDataType);
		~Shader();

	private:
		unsigned int m_shaderID;
		bool m_ShadersLoadedSuccessfully = false;

		std::string m_vertexShaderFilePath;
		std::string m_fragmentShaderFilePath;


		void CompileShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
		std::pair<std::string, std::string> GetShaderCodeFromFilePath(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	};

}