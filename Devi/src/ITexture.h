#pragma once

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

	};

}