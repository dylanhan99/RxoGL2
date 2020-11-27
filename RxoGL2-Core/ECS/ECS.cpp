#include "ECS.h"

namespace ECS
{
	// Entity
	void Entity::OnUpdate(float deltatime)
	{

	}

	void Entity::OnDraw()
	{

	}

	// Entity Manager
	void EntityManager::OnUpdate(float deltatime)
	{
		for (auto& e : m_Entities) e->OnUpdate(deltatime);
	}
	void EntityManager::OnDraw()
	{
		for (auto& e : m_Entities) e->OnDraw();
	}
	void EntityManager::Refresh()
	{
		m_Entities.erase(std::remove_if(std::begin(m_Entities), std::end(m_Entities), [](const sPtrEntity& entity)
			{
				return !entity->Active();
			}),
			std::end(m_Entities));
	}

}