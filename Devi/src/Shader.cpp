#include "Shader.h"
#include "Math/glm/mat4x4.hpp"
#include "Math/glm/vec3.hpp"
#include "Math/glm/vec4.hpp"
#include "Math/glm/gtc/matrix_transform.hpp"
#include "Math/glm/gtc/type_ptr.hpp"
#include <glad/glad.h>

namespace Devi
{

	Shader::Shader(const std::string& shaderName,
		const std::string& vertexShaderFilePath, 
		const std::string& fragmentShaderFilePath,
		std::optional<std::string> tessellationControlShaderFilePath,
		std::optional<std::string> tessellationEvaluationShaderFilePath)
		:m_shaderName(shaderName),
		 m_vertexShaderFilePath(vertexShaderFilePath),
		 m_fragmentShaderFilePath(fragmentShaderFilePath),
		 m_tessellationControlShaderFilePath(tessellationControlShaderFilePath),
		 m_tessellationEvaluationShaderFilePath(tessellationEvaluationShaderFilePath)
	{
		GetShaderCodeFromFilePaths();
		CompileShaders();
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

			else if (uniformDataType == UniformDataType::UNSIGNEDINT)
			{
				glUniform1i(glGetUniformLocation(m_shaderID, uniformName.c_str()), std::any_cast<unsigned int>(uniformValue));
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
			DEVI_ERROR(std::string(e.what()) + " for uniform variable: " + uniformName , __FILE__, __LINE__);
		}
	}

	void Shader::SetShaderFilePath(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath
		, std::optional<std::string> tessellationControlShaderFilePath,
		std::optional<std::string> tessellationEvaluationShaderFilePath)
	{
		m_vertexShaderFilePath = vertexShaderFilePath;
		m_fragmentShaderFilePath = fragmentShaderFilePath;
		m_tessellationControlShaderFilePath = tessellationControlShaderFilePath;
		m_tessellationEvaluationShaderFilePath = tessellationEvaluationShaderFilePath;

		GetShaderCodeFromFilePaths();
		CompileShaders();
	}

	std::string Shader::GetName() const
	{
		return m_shaderName;
	}

	void Shader::CompileShaders()
	{
		//create vertex shader
		const char* vsCode = m_vertexShaderCode.c_str();
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

		//create fragment shader
		const char* fsCode = m_fragmentShaderCode.c_str();

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

		//optional tesselation control shader
		if (m_tessellationControlShaderFilePath.has_value())
		{
			const char* tcsCode = m_tessellationControlShaderCode.c_str();
			unsigned int tcsShader = glCreateShader(GL_TESS_CONTROL_SHADER);
			glShaderSource(tcsShader, 1, &tcsCode, nullptr);
			glCompileShader(tcsShader);

			glGetShaderiv(tcsShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(tcsShader, 512, NULL, infoLog);
				DEVI_ERROR("compilation failed: " + m_tessellationControlShaderFilePath.value(), __FILE__, __LINE__);
			}
			else
			{
				glAttachShader(m_shaderID, tcsShader);
				//glDeleteShader(tcsShader);
			}
		}

		//optional tesselation evaluation shader
		if (m_tessellationEvaluationShaderFilePath.has_value())
		{
			const char* tesCode = m_tessellationEvaluationShaderCode.c_str();
			unsigned int tesShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
			glShaderSource(tesShader, 1, &tesCode, nullptr);
			glCompileShader(tesShader);

			glGetShaderiv(tesShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(tesShader, 512, NULL, infoLog);
				DEVI_ERROR("compilation failed: " + m_tessellationEvaluationShaderFilePath.value(), __FILE__, __LINE__);
			}
			else
			{
				glAttachShader(m_shaderID, tesShader);
				//glDeleteShader(tesShader);
			}
		}

		//linking

		glLinkProgram(m_shaderID);

		glGetProgramiv(m_shaderID, GL_LINK_STATUS, &success);
		
		if (!success) {
			glGetProgramInfoLog(m_shaderID, 512, NULL, infoLog);
			DEVI_ERROR("Linking error with shaders: " + m_fragmentShaderFilePath + " and " + m_vertexShaderFilePath, __FILE__, __LINE__);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Devi::Shader::GetShaderCodeFromFilePaths()
	{
		std::stringstream vertexShaderStream;
		std::ifstream vertexShaderFile;
		vertexShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		try
		{
			vertexShaderFile.open(m_vertexShaderFilePath);

			vertexShaderStream << vertexShaderFile.rdbuf();

			m_vertexShaderCode = vertexShaderStream.str();
		}
		catch (...)
		{
			DEVI_ERROR("Vertex shader file path failed to load for: " + m_vertexShaderFilePath, __FILE__, __LINE__);
		}

		std::stringstream fragmentShaderStream;
		std::ifstream fragmentShaderFile;
		fragmentShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

		try
		{
			fragmentShaderFile.open(m_fragmentShaderFilePath);

			fragmentShaderStream << fragmentShaderFile.rdbuf();

			m_fragmentShaderCode = fragmentShaderStream.str();
		}
		catch (...)
		{
			DEVI_ERROR("Fragment shader file path failed to load for: " + m_fragmentShaderFilePath, __FILE__, __LINE__);
		}

		if (m_tessellationControlShaderFilePath.has_value())
		{
			std::stringstream tessellationControlShaderStream;
			std::ifstream tessellationControlShaderFile;
			tessellationControlShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

			try
			{
				tessellationControlShaderFile.open(m_tessellationControlShaderFilePath.value());

				tessellationControlShaderStream << tessellationControlShaderFile.rdbuf();

				m_tessellationControlShaderCode = tessellationControlShaderStream.str();
			}
			catch (...)
			{
				DEVI_ERROR("tessellation control shader file path failed to load for: " + m_fragmentShaderFilePath, __FILE__, __LINE__);
			}
		}


		if (m_tessellationControlShaderFilePath.has_value())
		{
			std::stringstream tessellationEvaluationShaderStream;
			std::ifstream tessellationEvaluationShaderFile;
			tessellationEvaluationShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
			try
			{
				tessellationEvaluationShaderFile.open(m_tessellationEvaluationShaderFilePath.value());

				tessellationEvaluationShaderStream << tessellationEvaluationShaderFile.rdbuf();

				m_tessellationEvaluationShaderCode = tessellationEvaluationShaderStream.str();
			}
			catch (...)
			{
				DEVI_ERROR("tessellation evaluation shader file path failed to load for: " + m_fragmentShaderFilePath, __FILE__, __LINE__);
			}
		}
	}
}