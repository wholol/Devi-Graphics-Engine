#pragma once
#include <string_view>
#include <string>
#include <iostream>

namespace Devi
{
	/**
	* Logger class. Responsible for logging messages to the iostream.
	**/
	class Log
	{
	public:

		static void logTrace(const std::string_view& errorMessage, const std::string& fileLocation, int line);
		static void logDebug(const std::string_view& errorMessage, const std::string& fileLocation, int line);
		static void logInfo(const std::string_view& errorMessage, const std::string& fileLocation, int line);
		static void logWarn(const std::string_view& errorMessage, const std::string& fileLocation, int line);
		static void logError(const std::string_view& errorMessage, const std::string& fileLocation, int line);
		static void logFatal(const std::string_view& errorMessage, const std::string& fileLocation, int line);
	
	};
}

#define DEVI_TRACE(errorMsg, fileLocation, lineNumber) ::Devi::Log::logTrace(errorMsg, fileLocation, lineNumber)
#define DEVI_DEBUG(errorMsg, fileLocation, lineNumber)  ::Devi::Log::logDebug(errorMsg, fileLocation, lineNumber)
#define DEVI_INFO(errorMsg, fileLocation, lineNumber)  ::Devi::Log::logInfo(errorMsg, fileLocation, lineNumber)
#define DEVI_WARN(errorMsg, fileLocation, lineNumber)  ::Devi::Log::logWarn(errorMsg, fileLocation, lineNumber)
#define DEVI_ERROR(errorMsg, fileLocation, lineNumber)  ::Devi::Log::logError(errorMsg, fileLocation, lineNumber)
#define DEVI_FATAL(errorMsg, fileLocation, lineNumber)  ::Devi::Log::logFatal(errorMsg, fileLocation, lineNumber)
