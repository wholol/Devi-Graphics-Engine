#pragma once

namespace Devi
{
	/**
	* Interface for Texture classes.
	**/
	class ITexture
	{
	public:

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	};

}