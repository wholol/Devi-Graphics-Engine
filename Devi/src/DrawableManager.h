#pragma once
#include <unordered_map>
#include "IDrawable.h"


namespace Devi
{
	using DrawablePtr = std::shared_ptr<IDrawable>;

	class DrawableManager
	{
	public:
		void AddDrawable(const std::string& name, DrawablePtr drawablePtr);
		DrawablePtr GetDrawable(const std::string& name) const;

	private:
		std::vector<DrawablePtr> m_drawables;
		std::unordered_map<std::string, DrawablePtr> m_drawableMap;
	};
}
