#pragma once
#include "../Constants.h"
#include "../Utils/Font.h"

namespace Singletons
{
	class FontCache
	{
	private:
		static sPtrFontCache m_Instance;
		std::unordered_map<std::string, sPtrFont> m_Fonts;
	public:
		static inline sPtrFontCache Instance()
		{
			if (m_Instance == NULL)
				m_Instance = std::make_shared<FontCache>();
			return m_Instance;
		}
		sPtrFont AddFont(std::string name, std::string path);

		// Getters/Setters
		inline sPtrFont GetFont(std::string name) const { return m_Fonts.at(name); }
	};
}