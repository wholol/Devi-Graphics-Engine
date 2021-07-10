#include "Shader.h"
#include <glad/glad.h>

Devi::Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	auto [vertexShaderCode, fragmentShaderCode] = GetShaderCodeFromFilePath(vertexShaderFilePath, fragmentShaderFilePath);
	CompileShader(vertexShaderCode, fragmentShaderCode);
}

void Devi::Shader::Bind()
{
	glUseProgram(m_shaderID);
}

void Devi::Shader::UnBind()
{
	glUseProgram(0);
}

void Devi::Shader::SetUniform(const std::string& uniformName, const std::any& uniformValue, UniformDataType uniformDataType)
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

		else if (uniformDataType == UniformDataType::MAT2)
		{
			//TODO
		}

		else if (uniformDataType == UniformDataType::MAT3)
		{
			//TODO
		}

		else if (uniformDataType == UniformDataType::MAT4)
		{
			//TODO
		}
		else
		{
			//throw Exception::NotImplementedException("uniform data type not implemented", __FILE__, __LINE__);
			//Uniform type not implemented!
		}
	}
	catch (std::bad_any_cast& e)
	{
		DEVI_ERROR(e.what(), __FILE__, __LINE__);
	}

	
		
}

Devi::Shader::~Shader()
{
	UnBind();
}

void Devi::Shader::CompileShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
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
		DEVI_ERROR("Vertex shader failed to compile.", __FILE__, __LINE__);
	}
	
	const char* fsCode = fragmentShaderCode.c_str();

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(fragmentShader, 1, &fsCode, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		DEVI_ERROR("Fragment shader failed to compile.", __FILE__, __LINE__);
	}


	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertexShader);
	glAttachShader(m_shaderID, fragmentShader);
	
	glLinkProgram(m_shaderID);
	//TODO: Check for linking error for shader.
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderID, 512, NULL, infoLog);
		DEVI_ERROR("Linking error with shaders.", __FILE__, __LINE__);
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
	catch (std::ifstream::failure& e)
	{
		DEVI_ERROR(".Vertex shader file path failed to load for: " + vertexShaderFilePath, __FILE__, __LINE__);
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
	catch (std::ifstream::failure& e)
	{
		DEVI_ERROR(".Fragment shader file path failed to load for: " + vertexShaderFilePath, __FILE__, __LINE__);
	}

	return std::make_pair(vertexShaderCode, fragmentShaderCode);
}
