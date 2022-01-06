#include "ECS.h"
#include <gtx/projection.hpp>
#include "../Graphics/Renderers/BatchRenderer.h"
#include "../Layering/Layer.h"

namespace ECS
{
	// Entity
	Entity::Entity(std::string name) : 
		m_Name(name)
	{
		if (name == "")
		{
			m_Name = "Entity" + ID();
		}
	}
	void Entity::OnAwake()
	{
		for (auto c : m_Components) c->OnAwake();
	}
	void Entity::OnStart()
	{
		for (auto c : m_Components) c->OnStart();
	}
	void Entity::OnStop()
	{
		for (auto c : m_Components) c->OnStop();
	}
	void Entity::OnUpdate(float deltatime)
	{
		for (auto c : m_Components) c->OnUpdate(deltatime);
	}
	void Entity::OnDraw()
	{
		for (auto c : m_Components) c->OnDraw();
	}
	void Entity::OnCollisionEnter(sPtrCollidableComponent component)
	{
		for (auto c : m_Components) c->OnCollisionEnter(component);
	}
	void Entity::OnCollisionStay(sPtrCollidableComponent component)
	{
		for (auto c : m_Components) c->OnCollisionStay(component);
	}
	void Entity::OnCollisionExit(sPtrCollidableComponent component)
	{
		for (auto c : m_Components) c->OnCollisionExit(component);
	}

	// Entity List
	void EntityList::OnAwake()
	{
		for (auto e : m_Entities) e->OnAwake();
	}
	void EntityList::OnStart()
	{
		for (auto e : m_Entities) e->OnStart();
	}
	void EntityList::OnStop()
	{
		for (auto e : m_Entities) e->OnStop();
	}
	void EntityList::OnUpdate(float deltatime)
	{
		for (auto e : m_Entities) e->OnUpdate(deltatime);
	}
	void EntityList::OnDraw()
	{
		for (auto e : m_Entities) e->OnDraw();
	}
	sPtrEntity EntityList::AddEntity(Entity& e)
	{
		sPtrEntity sPtr{ &e };
		sPtr->m_sPtrThis = sPtr;
		m_Entities.push_back(sPtr);
		m_Entities_Tags[sPtr->Tag()].push_back(sPtr);
		return sPtr;
	}
	void EntityList::Refresh()
	{
		m_Entities.erase(std::remove_if(std::begin(m_Entities), std::end(m_Entities), [](const sPtrEntity& entity)
			{
				return !entity->Active();
			}),
			std::end(m_Entities));
	}

	// Collidable Component
	CollidableComponent::CollidableComponent(RXOposition* position)
		: m_Position(position),
		m_IsColliding(false)
	{
		
	}
	void CollidableComponent::OnDraw()
	{
		m_Entity->Layer()->GetRenderer()->Submit(this);
		//DrawOutline();
	}
	//bool CollidableComponent::CheckCollision(sPtrCollidableComponent other)
	//{
	//	return false;
	//}
}