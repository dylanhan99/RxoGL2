#include "StandardComponents.h"
#include "../Singletons/TextureCache.h"

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

	void Sprite::Add(std::string framename, float bl_x, float bl_y, float w, float h) // For SpriteSheet
	{
		switch (m_IsSpriteSheet) {
		case true:
			bl_x /= m_TextureData->Height();
			bl_y /= m_TextureData->Width();
			w /= m_TextureData->Height();
			h /= m_TextureData->Width();
			m_TexCoordsCache[framename] = TexCoords
			{
				glm::vec2(bl_x		, bl_y),	 // bl
				glm::vec2(bl_x + w	, bl_y),	 // br
				glm::vec2(bl_x + w	, bl_y + h), // tr
				glm::vec2(bl_x		, bl_y + h)  // tl 
			};
			break;
		default:
			break;
		}
	}

}