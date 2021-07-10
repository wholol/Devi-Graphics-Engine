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

		static void LogTrace(const std::string_view& errorMessage, const std::string& fileLocation, int line);
		static void LogTrace(const std::string_view& errorMessage);
					
		static void LogDebug(const std::string_view& errorMessage, const std::string& fileLocation, int line);
		static void LogDebug(const std::string_view& errorMessage);
					
		static void LogInfo(const std::string_view& errorMessage, const std::string& fileLocation, int line);
		static void LogInfo(const std::string_view& errorMessage);
					
		static void LogWarn(const std::string_view& errorMessage, const std::string& fileLocation, int line);
		static void LogWarn(const std::string_view& errorMessage);
					
		static void LogError(const std::string_view& errorMessage, const std::string& fileLocation, int line);
		static void LogError(const std::string_view& errorMessage);
					
		static void LogFatal(const std::string_view& errorMessage, const std::string& fileLocation, int line);
		static void LogFatal(const std::string_view& errorMessage);

	};
}

#define DEVI_TRACE(errorMsg, fileLocation, lineNumber) ::Devi::Log::LogTrace(errorMsg, fileLocation, lineNumber)

#define DEVI_DEBUG(errorMsg, fileLocation, lineNumber)  ::Devi::Log::LogDebug(errorMsg, fileLocation, lineNumber)

#define DEVI_INFO(errorMsg, fileLocation, lineNumber)  ::Devi::Log::LogInfo(errorMsg, fileLocation, lineNumber)

#define DEVI_WARN(errorMsg, fileLocation, lineNumber)  ::Devi::Log::LogWarn(errorMsg, fileLocation, lineNumber)

#define DEVI_ERROR(errorMsg, fileLocation, lineNumber)  ::Devi::Log::LogError(errorMsg, fileLocation, lineNumber)

#define DEVI_FATAL(errorMsg, fileLocation, lineNumber)  ::Devi::Log::LogFatal(errorMsg, fileLocation, lineNumber)