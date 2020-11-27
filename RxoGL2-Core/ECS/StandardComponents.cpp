#include "StandardComponents.h"

namespace ECS
{
	Sprite::Sprite(const std::string& textureName, const std::string& filePath, float r, float g, float b, float a, bool isSpriteSheet)
		: m_TextureData(Singletons::TextureCache::Instance()->AddTexture(filePath)),
		m_TexCoords({ glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }),
		m_Color({r, g, b, a}),
		m_IsSpriteSheet(isSpriteSheet)
	{

	}

	Sprite::Sprite(float r, float g, float b, float a)
		: m_TexCoords({ glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }),
		m_Color({r, g, b, a})
	{

	}
}