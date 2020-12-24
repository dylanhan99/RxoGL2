#include "FontCache.h"
#include "../Utils/Font.h"

namespace Singletons
{
	sPtrFontCache FontCache::m_Instance = NULL;

	sPtrFont FontCache::AddFont(std::string name, std::string path)
	{
		m_Fonts[name] = std::make_shared<Font>(path, 48);
		return GetFont(name);
	}
}