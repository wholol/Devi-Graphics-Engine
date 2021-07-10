#pragma once
#include <exception>
#include <string>

namespace Devi
{
	namespace Exception
	{
		/**
		* Not implemented exception class. Throws exception if the caller uses an unimplemented functionality.
		**/
		class NotImplementedException : public std::exception
		{
		public:
			
			NotImplementedException(const std::string& errorMessage, const std::string& fileLocation, int lineNumber) noexcept
				:exception(( errorMessage + "file location: " + fileLocation + " .line number: " + std::to_string(lineNumber)).c_str() )
			{}
		};
	}
}
