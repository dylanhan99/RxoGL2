#pragma once
#include "ECS.h"
#include "../Event/Event.h"
#include "../Singletons/EventCache.h"

namespace ECS
{
	class Transform : public Component
	{
	private:
		RXOposition m_Position;
		RXOsize m_Size;
		Singletons::EventDispatcher m_OnPosChange;
	public:
		Transform(float x, float y, float z) : m_Position(RXOposition(x, y, z, 1)) {}
		// Getters/Setters
		//inline const RXOposition&	GetPosition() const						{ return m_Position; }
		inline  RXOposition&	GetPosition() 						{ return m_Position; }
		inline		 void			SetPosition(float x, float y, float z)	{ m_Position.x = x; m_Position.y = y; m_Position.z = z; m_OnPosChange.DispatchEvent(EVENT_NAME_OnPosChange); }
		inline		 void			SetPosition(RXOposition& pos)			{ m_Position = pos; m_OnPosChange.DispatchEvent(EVENT_NAME_OnPosChange); }
		inline const RXOsize&		GetSize() const							{ return m_Size; }
		inline		 void			SetSize(RXOsize& size)					{ m_Size = size; }
		inline		 void			SetSize(float width, float height)	{ m_Size.x = width; m_Size.y = height; }
		inline const Singletons::EventDispatcher& OnPosChange() const		{ return m_OnPosChange; }
	};

	class Sprite : public RenderableComponent
	{
		struct TexCoords
		{
			glm::vec2 bl, br, tr, tl;
		};
	private:
		std::string m_FrameName;
		sPtrTextureData m_TextureData;
		RXOcolor m_Color;
		TexCoords m_TexCoords;
		std::unordered_map<std::string, TexCoords> m_TexCoordsCache;
		bool m_IsSpriteSheet = false;
	public:
		Sprite(std::string textureName, std::string filePath, float r, float g, float b, float a, bool isTextureSheet = false);
		Sprite(float r, float g, float b, float a);

		void OnDraw() override;

		void Add(std::string framename, float bl_x, float bl_y, float w, float h); // For SpriteSheet

		// Getters/Setters
		inline const sPtrTextureData& GetTexture() const { return m_TextureData; }
		inline const RXOcolor& GetColor() const { return m_Color; }
		inline const TexCoords& GetCoords() const
		{
			switch (m_IsSpriteSheet) {
			case true:
				if (!m_TexCoordsCache.empty())
					return m_TexCoordsCache.at(m_FrameName);
				break;
			default:
				return m_TexCoords;
			}
		}
	};

	class Label : public RenderableComponent
	{
	private:
		std::string m_Text;
		float m_Scale;
		std::string m_FontName;
		RXOcolor m_Color;
	public:
		Label(std::string text, std::string fontName, float scale);
		void OnDraw() override;

		// Getters/Setters
		inline const std::string&	GetText()		const { return m_Text; }
		inline const float&			GetScale()		const { return m_Scale; }
		inline const std::string&	GetFontName()	const { return m_FontName; }
		inline const RXOcolor&		GetColor()		const { return m_Color; }
	};

	class PolygonCollider : public CollidableComponent
	{
	private:
		std::vector<glm::vec3> m_ColliderPointCoords;

		void AddToPhysicsManager() override;
	public:
		PolygonCollider(RXOposition position, std::vector<glm::vec3> coords /*= Default Coords*/);
		std::pair<float, float> Project(glm::vec3 edge) override;

		// Getters/Setters
		inline const std::vector<glm::vec3>& GetPoints() const { return m_ColliderPointCoords; }
		const std::pair<glm::vec3, glm::vec3> GetMinMax(glm::vec3 edge) const;
	};

	class CircleCollider : public CollidableComponent
	{
	private:
		float m_Radius;
	public:
		std::pair<float, float> Project(glm::vec3 edge) override;
		// Getters/Setters
		inline const float& GetRadius() const { return m_Radius; }
	};
}