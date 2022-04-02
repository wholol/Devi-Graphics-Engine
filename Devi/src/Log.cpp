#include "Log.h"

namespace Devi
{

	void Devi::Log::LogTrace(const std::string_view & errorMessage, const std::string & fileLocation, int line)
	{
		std::cout << "[TRACE]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
	}

	void Log::LogTrace(const std::string_view & errorMessage)
	{
		std::cout << "[TRACE]: " << errorMessage << std::endl;
	}

	void Devi::Log::LogDebug(const std::string_view & errorMessage, const std::string & fileLocation, int line)
	{
		std::cout << "[DEBUG]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
	}

	void Log::LogDebug(const std::string_view & errorMessage)
	{
		std::cout << "[DEBUG]: " << errorMessage << std::endl;
	}

	void Devi::Log::LogInfo(const std::string_view & errorMessage, const std::string & fileLocation, int line)
	{
		std::cout << "[INFO]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
	}

	void Log::LogInfo(const std::string_view & errorMessage)
	{
		std::cout << "[INFO]: " << errorMessage << std::endl;
	}

	void Devi::Log::LogWarn(const std::string_view & errorMessage, const std::string & fileLocation, int line)
	{
		std::cout << "[WARN]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
	}

	void Log::LogWarn(const std::string_view & errorMessage)
	{
		std::cout << "[WARN]: " << errorMessage << std::endl;
	}

	void Devi::Log::LogError(const std::string_view & errorMessage, const std::string & fileLocation, int line)
	{
		std::cerr << "[ERROR]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
	}

	void Log::LogError(const std::string_view & errorMessage)
	{
	}

	void Devi::Log::LogFatal(const std::string_view & errorMessage, const std::string & fileLocation, int line)
	{
		std::cerr << "[FATAL]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
	}

}