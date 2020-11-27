#pragma once
#include "ECS.h"
#include "../Event/Event.h"
#include "../Singletons/TextureCache.h"

namespace ECS
{
	class Transform : public Component
	{
	private:
		RXOposition m_Position;
		RXOsize m_Size;
		Event::EventDispatcher m_OnPosChange;
	public:
		// Getters/Setters
		inline const RXOposition& Position() const					  { return m_Position; }
		inline		 void		  Position(float x, float y, float z) { m_Position.x = x; m_Position.y = y; m_Position.z = z; m_OnPosChange.DispatchEvent(EVENT_NAME_OnPosChange); }
		inline		 void		  Position(RXOposition& pos)		  { m_Position = pos; m_OnPosChange.DispatchEvent(EVENT_NAME_OnPosChange); }
		inline const RXOsize& Size() const		  { return m_Size; }
		inline		 void	  Size(RXOsize& size) { m_Size = size; }
		inline const Event::EventDispatcher& OnPosChange() const { return m_OnPosChange; }
	};

	class Sprite : public RenderableComponent
	{
		struct TexCoords
		{
			glm::vec2 bl, br, tr, tl;
		};
	private:
		sPtrTextureData m_TextureData;
		RXOcolor m_Color;
		TexCoords m_TexCoords;
		std::unordered_map<std::string, TexCoords> m_TexCoordsCache;
		bool m_IsSpriteSheet = false;
	public:
		Sprite(const std::string& textureName, const std::string& filePath, float r, float g, float b, float a, bool isTextureSheet = false);
		Sprite(float r, float g, float b, float a);
		void Add(std::string framename, float bl_x, float bl_y, float w, float h) // For SpriteSheet
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

		// Getters/Setters
		inline const sPtrTextureData& Texture() const { return m_TextureData; }
		inline const RXOcolor& Color() const { return m_Color; }
		inline const TexCoords& Coords(std::string framename = "") const 
		{
			switch (m_IsSpriteSheet) {
			case true:
				if (!m_TexCoordsCache.empty())
					return m_TexCoordsCache.at(framename);
				break;
			default:
				return m_TexCoords;
			}
		}
	};

	class Label : public RenderableComponent
	{

	};
}