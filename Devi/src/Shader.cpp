#include "Shader.h"
#include "Math/glm/mat4x4.hpp"
#include "Math/glm/vec3.hpp"
#include "Math/glm/vec4.hpp"
#include "Math/glm/gtc/matrix_transform.hpp"
#include "Math/glm/gtc/type_ptr.hpp"
#include <glad/glad.h>

namespace Devi
{

	Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
		:m_vertexShaderFilePath(vertexShaderFilePath),
		 m_fragmentShaderFilePath(fragmentShaderFilePath)
	{
		auto[vertexShaderCode, fragmentShaderCode] = GetShaderCodeFromFilePath(m_vertexShaderFilePath, m_fragmentShaderFilePath);
		CompileShader(vertexShaderCode, fragmentShaderCode);
	}

	void Shader::Bind()
	{
		glUseProgram(m_shaderID);
	}

	void Shader::UnBind()
	{
		glUseProgram(0);
	}

	void Shader::SetUniform(const std::string& uniformName, const std::any& uniformValue, UniformDataType uniformDataType)
	{
		try
		{
			if (uniformDataType == UniformDataType::FLOAT)
			{
				glUniform1f(glGetUniformLocation(m_shaderID, uniformName.c_str()), std::any_cast<float>(uniformValue));
			}

			else if (uniformDataType == UniformDataType::INT)
			{
				glUniform1i(glGetUniformLocation(m_shaderID, uniformName.c_str()), std::any_cast<int>(uniformValue));
			}

			else if (uniformDataType == UniformDataType::BOOL)
			{
				glUniform1i(glGetUniformLocation(m_shaderID, uniformName.c_str()), std::any_cast<bool>(uniformValue));
			}

			else if (uniformDataType == UniformDataType::VEC2)
			{
				glUniform2fv(glGetUniformLocation(m_shaderID, uniformName.c_str()), 1, &std::any_cast<glm::vec2>(uniformValue)[0]);
			}

			else if (uniformDataType == UniformDataType::VEC3)
			{
				glUniform3fv(glGetUniformLocation(m_shaderID, uniformName.c_str()), 1, &std::any_cast<glm::vec3>(uniformValue)[0]);
			}

			else if (uniformDataType == UniformDataType::VEC4)
			{
				glUniform4fv(glGetUniformLocation(m_shaderID, uniformName.c_str()), 1, &std::any_cast<glm::vec4>(uniformValue)[0]);
			}
			else if (uniformDataType == UniformDataType::MAT4)
			{
				// glm::value_ptr is the same as &(glm::mat4(uniformvalue)[0][0]); --getting the address to the first pointer--.
				glUniformMatrix4fv(glGetUniformLocation(m_shaderID, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(std::any_cast<glm::mat4>(uniformValue)));
			}
			else
			{
				//TODO: since we will have multiple shaders, we need to define the shader being used.
				throw Exception::NotImplementedException("uniform data type not implemented.", __FILE__, __LINE__);
			}
		}
		catch (std::exception& e)
		{
			DEVI_ERROR(std::string(e.what()), __FILE__, __LINE__);
		}
	}

	void Shader::SetShaderFilePath(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		m_vertexShaderFilePath = vertexShaderFilePath;
		m_fragmentShaderFilePath = fragmentShaderFilePath;

		auto[vertexShaderCode, fragmentShaderCode] = GetShaderCodeFromFilePath(m_vertexShaderFilePath, m_fragmentShaderFilePath);
		CompileShader(vertexShaderCode, fragmentShaderCode);
	}

	void Shader::CompileShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
	{

		const char* vsCode = vertexShaderCode.c_str();
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, &vsCode, nullptr);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			DEVI_ERROR("compilation failed: " + m_fragmentShaderFilePath, __FILE__, __LINE__);
		}

		const char* fsCode = fragmentShaderCode.c_str();

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragmentShader, 1, &fsCode, nullptr);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			DEVI_ERROR("compilation failed: " + m_fragmentShaderFilePath, __FILE__, __LINE__);
		}

		m_shaderID = glCreateProgram();
		glAttachShader(m_shaderID, vertexShader);
		glAttachShader(m_shaderID, fragmentShader);
		glLinkProgram(m_shaderID);

		glGetProgramiv(m_shaderID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_shaderID, 512, NULL, infoLog);
			DEVI_ERROR("Linking error with shaders: " + m_fragmentShaderFilePath + " and " + m_vertexShaderFilePath, __FILE__, __LINE__);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}

	std::pair<std::string, std::string> Devi::Shader::GetShaderCodeFromFilePath(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		std::stringstream vertexShaderStream;
		std::string vertexShaderCode;

		std::ifstream vertexShaderFile;
		vertexShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		try
		{
			vertexShaderFile.open(vertexShaderFilePath);

			vertexShaderStream << vertexShaderFile.rdbuf();

			vertexShaderCode = vertexShaderStream.str();
		}
		catch (...)
		{
			DEVI_ERROR("Vertex shader file path failed to load for: " + m_vertexShaderFilePath, __FILE__, __LINE__);
		}

		std::stringstream fragmentShaderStream;
		std::string fragmentShaderCode;

		std::ifstream fragmentShaderFile;
		fragmentShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

		try
		{
			fragmentShaderFile.open(fragmentShaderFilePath);

			fragmentShaderStream << fragmentShaderFile.rdbuf();

			fragmentShaderCode = fragmentShaderStream.str();
		}
		catch (...)
		{
			DEVI_ERROR("Fragment shader file path failed to load for: " + m_fragmentShaderFilePath, __FILE__, __LINE__);
		}

		return std::make_pair(vertexShaderCode, fragmentShaderCode);
	}
}