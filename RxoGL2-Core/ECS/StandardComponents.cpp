#include "StandardComponents.h"
#include "../Singletons/TextureCache.h"
#include "../Graphics/Renderers/BatchRenderer.h"
#include "../Layering/Layer.h"
#include "../Utils/Timer.h"

namespace ECS
{
	//Sprite
	Sprite::Sprite(std::string textureName, std::string filePath, float r, float g, float b, float a, bool isSpriteSheet)
		: m_FrameName(textureName),
		m_TextureData(Singletons::TextureCache::Instance()->AddTexture(filePath)),
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
	void Sprite::OnDraw()
	{
		//{
		//	Timer();
		//	auto d = std::dynamic_pointer_cast<ECS::Sprite>(m_sPtrThis);
		//}
		m_Entity->Layer()->GetRenderer()->Submit(this); 
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

	// Label
	Label::Label(std::string text, std::string fontName, float scale)
		: m_Text(text), m_FontName(fontName), m_Scale(scale), m_Color(0.f, 0.f, 0.f, 1.f)
	{

	}
	void Label::OnDraw()
	{
		m_Entity->Layer()->GetRenderer()->Submit(this);
	}
}