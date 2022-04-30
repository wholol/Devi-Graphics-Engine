#include "IDrawable.h"

namespace Devi
{
	Drawable::Drawable(const std::string & name)
		:m_name(name)
	{
	}

	std::string Drawable::GetName() const
	{
		return m_name;
	}
}

