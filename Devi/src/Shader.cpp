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
	if (uniformDataType == UniformDataType::FLOAT)
	{
		//TODO
	}

	else if (uniformDataType == UniformDataType::INT)
	{
		//TODO
	}

	else if (uniformDataType == UniformDataType::BOOL)
	{
		//TODO
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
		
}

Devi::Shader::~Shader()
{
	UnBind();
}

void Devi::Shader::CompileShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
{
	unsigned int vertexShader;
	const char* vertexShaderFilePath = vertexShaderCode.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderFilePath, nullptr);
	glCompileShader(vertexShader);
	// TODO: check for compilation error failures for the shader.

	unsigned int fragmentShader;
	const char* fragmentShaderFilePath = fragmentShaderCode.c_str();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &fragmentShaderFilePath, nullptr);
	//TODO: check for compilation error failures for the shader.

	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertexShader);
	glAttachShader(m_shaderID, fragmentShader);
	
	glLinkProgram(m_shaderID);
	//TODO: Check for linking error for shader.

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
		std::cerr << e.what() << " .Vertex shader file path failed to load for: " << vertexShaderFilePath << std::endl;
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
		std::cerr << e.what() << " .Fragment shader file path failed to load for: " << fragmentShaderFilePath << std::endl;
	}

	return std::make_pair(vertexShaderCode, fragmentShaderCode);
}
