#include "DrawableManager.h"

namespace Devi
{
	void DrawableManager::AddDrawable(const std::string & name, DrawablePtr drawable)
	{
		auto findDrawableName = m_drawableMap.find(name);

		if (findDrawableName != m_drawableMap.end())
		{
			DEVI_ERROR("Drawable: " + name + " not added. The name already exists.", __FILE__, __LINE__);
		}
		else
		{
			m_drawableMap.insert(std::make_pair(name, drawable));
			m_drawables.push_back(drawable);
		}
	}

	DrawablePtr DrawableManager::GetDrawable(const std::string& name) const
	{
		auto findDrawableName = m_drawableMap.find(name);

		if (findDrawableName != m_drawableMap.end())
		{
			return findDrawableName->second;
		}
		else
		{
			DEVI_ERROR("Drawable: " + name + " not found.", __FILE__, __LINE__);
		}

		return nullptr;
	}
	const std::vector<DrawablePtr>& DrawableManager::GetAllDrawables() const
	{
		return m_drawables;
	}
}

