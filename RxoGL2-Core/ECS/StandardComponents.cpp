#include "StandardComponents.h"
#include "../Singletons/TextureCache.h"
#include "../Graphics/Renderers/BatchRenderer.h"
#include "../Layering/Layer.h"
#include "../Physics/PhysicsManager.h"
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

	// PolygonCollider : Collidable
	PolygonCollider::PolygonCollider(RXOposition* position, std::vector<glm::vec3> coords)
		: CollidableComponent(position),
		m_ColliderPointCoords(coords)
	{
		UpdateEdges();
	}
	void PolygonCollider::AddToPhysicsManager()
	{
		m_Entity->Layer()->GetPhysicsManager()->Add(std::static_pointer_cast<PolygonCollider>(m_sPtrThis));
	}
	void PolygonCollider::UpdateEdges()
	{
		if(!m_Edges.empty())
			m_Edges.clear();
		for (size_t i = 0; i < m_ColliderPointCoords.size(); i++)
		{
			auto edge = m_ColliderPointCoords[i];
			switch (i)
			{
			case 0:
				edge = m_ColliderPointCoords[m_ColliderPointCoords.size() - 1] - m_ColliderPointCoords[i];
				m_Edges.push_back(edge);
				continue;
			default:
				edge = m_ColliderPointCoords[i] - m_ColliderPointCoords[i - 1];
				m_Edges.push_back(edge);
				continue;
			}
		}
	}
	std::pair<float, float> PolygonCollider::Project(glm::vec3 plane)
	{
		float min = NULL;
		float max = NULL;
		for (const auto& v : m_ColliderPointCoords)
		{
			float dot = v.x * plane.x + v.y * plane.y;
			if (min == NULL || dot < min)
				min = dot;
			if (max == NULL || dot > max)
				max = dot;
		}
		return std::pair<float, float>(min, max);
	}
	bool PolygonCollider::CheckCollision(sPtrCollidableComponent other)
	{
		auto thisCast  = std::static_pointer_cast<PolygonCollider>(m_sPtrThis);
		if (std::dynamic_pointer_cast<PolygonCollider>(other))
			return PhysicsManager::PolyPoly(thisCast, std::static_pointer_cast<PolygonCollider>(other));
		if (std::dynamic_pointer_cast<CircleCollider>(other))
			return PhysicsManager::PolyCircle(thisCast, std::static_pointer_cast<CircleCollider>(other));
		return false;
	}
	const std::vector<glm::vec3>& PolygonCollider::GetPlanes()
	{
		UpdateEdges();
		std::vector<glm::vec3> perpendicularPlanes;
		for (size_t i = 0; i < m_Edges.size() - 1; i++)
			perpendicularPlanes.push_back(glm::vec3(-m_Edges[i].y, m_Edges[i].x, m_Edges[i].z));
		return perpendicularPlanes;
	}

	// CircleCollider :: Collidable
	void CircleCollider::AddToPhysicsManager()
	{
		m_Entity->Layer()->GetPhysicsManager()->Add(std::static_pointer_cast<CircleCollider>(m_sPtrThis));
	}
	std::pair<float, float> CircleCollider::Project(glm::vec3 plane)
	{
		auto min = *m_Position - RXOposition(m_Radius, 0.f, 0.f, 0.f);
		auto max = *m_Position + RXOposition(m_Radius, 0.f, 0.f, 0.f);
		auto dotMin = min.x * plane.x + min.y * plane.y;
		auto dotMax = max.x * plane.x + max.y * plane.y;
		return std::pair<float, float>(dotMin, dotMax);
	}
	bool CircleCollider::CheckCollision(sPtrCollidableComponent other)
	{
		auto thisCast = std::static_pointer_cast<CircleCollider>(m_sPtrThis);
		if (std::dynamic_pointer_cast<PolygonCollider>(other))
			return PhysicsManager::CircleCircle(thisCast, std::static_pointer_cast<CircleCollider>(other));
		if (std::dynamic_pointer_cast<CircleCollider>(other))
			return PhysicsManager::PolyCircle(std::static_pointer_cast<PolygonCollider>(other), thisCast);
		return false;
	}
}