#pragma once
#include "../Constants.h"
#include "../Utils/Utilities.h"

class TextureData
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	unsigned int m_Width, m_Height, m_BPP;
public:
	TextureData(const std::string& path);
	~TextureData();
	void Load();
	inline void Bind(unsigned int slot = 0) const { glBindTextureUnit(slot, m_RendererID); }
	inline void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

	// Getters/Setters
	inline const unsigned int& ID()		{ return m_RendererID; }
	inline const unsigned int& Height() { return m_Height; }
	inline const unsigned int& Width()	{ return m_Width; }
};

namespace Singletons
{
	class TextureCache
	{
	private:
		static sPtrTextureCache m_Instance;
		std::unordered_map<std::string, sPtrTextureData> m_Textures;
	public:
		static inline sPtrTextureCache Instance()
		{
			if (m_Instance == NULL)
				m_Instance = std::make_shared<TextureCache>();
			return m_Instance;
		}
		sPtrTextureData AddTexture(std::string path);

		// Getters/Setters
		inline sPtrTextureData GetTexture(std::string path) const { return m_Textures.at(path); }
	};
}