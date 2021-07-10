#include "Log.h"

void Devi::Log::logTrace(const std::string_view & errorMessage, const std::string & fileLocation, int line)
{
	std::cout << "[TRACE]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
}

void Devi::Log::logDebug(const std::string_view & errorMessage, const std::string & fileLocation, int line)
{
	std::cout << "[DEBUG]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
}

void Devi::Log::logInfo(const std::string_view & errorMessage, const std::string & fileLocation, int line)
{
	std::cout << "[INFO]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
}

void Devi::Log::logWarn(const std::string_view & errorMessage, const std::string & fileLocation, int line)
{
	std::cout << "[WARN]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
}

void Devi::Log::logError(const std::string_view & errorMessage, const std::string & fileLocation, int line)
{
	std::cerr << "[ERROR]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
}

void Devi::Log::logFatal(const std::string_view & errorMessage, const std::string & fileLocation, int line)
{
	std::cerr << "[FATAL]: " << errorMessage << " " << fileLocation << " " << std::to_string(line) << std::endl;
}
