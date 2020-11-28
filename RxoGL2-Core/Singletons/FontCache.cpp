#include "FontCache.h"
#include "../Utils/Font.h"

namespace Singletons
{
	sPtrFontCache FontCache::m_Instance = NULL;

	sPtrFont FontCache::AddFont(std::string path)
	{
		m_Fonts[path] = std::make_shared<Font>(path, 48);
		return GetFont(path);
	}
}