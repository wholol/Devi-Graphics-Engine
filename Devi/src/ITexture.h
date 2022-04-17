#pragma once
#include <string>

namespace Devi
{
	/**
	* Interface for Texture classes.
	**/
	class ITexture
	{
	public:

		virtual void Bind(unsigned int activeTexture = 0) = 0;
		virtual void UnBind() = 0;
		virtual std::string GetName() const = 0;
	};

}