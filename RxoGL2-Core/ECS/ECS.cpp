#include "ECS.h"
#include <gtx/projection.hpp>

namespace ECS
{
	// Entity
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
	CollidableComponent::CollidableComponent()
		: m_IsColliding(false)
	{
		
	}
	void CollidableComponent::OnAwake()
	{
		AddToPhysicsManager();
	}
	bool CollidableComponent::CheckCollision(sPtrCollidableComponent other)
	{
		return false;
	}

	glm::vec3 Project(glm::vec3 vector, glm::vec3 plane)
	{
		return glm::proj(vector, plane);
	}
	//void CollidableComponent::AddToPhysicsManager()
	//{
	//	m_Entity->Layer()->GetPhysicsManager()->Add(std::static_pointer_cast<CollidableComponent>(m_sPtrThis));
	//}
}