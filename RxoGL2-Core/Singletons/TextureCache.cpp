#include "TextureCache.h"

TextureData::TextureData(const std::string& path)
	: m_FilePath(path)
{
	Load();
}

TextureData::~TextureData()
{
	if (m_LocalBuffer)
	{
		glDeleteTextures(1, &m_RendererID);
		delete m_LocalBuffer;
	}
}

void TextureData::Load()
{
	m_LocalBuffer = Utilities::LoadTexture(m_FilePath.c_str(), m_Width, m_Height);
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	Unbind();
}

namespace Singletons
{
	sPtrTextureCache TextureCache::m_Instance = NULL;

	sPtrTextureData TextureCache::AddTexture(std::string path)
	{
		m_Textures[path] = std::make_shared<TextureData>(path);
		return GetTexture(path);
	}
}