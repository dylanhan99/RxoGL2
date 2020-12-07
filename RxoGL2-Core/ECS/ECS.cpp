#include "ECS.h"

namespace ECS
{
	// Entity
	void Entity::OnUpdate(float deltatime)
	{
		for (auto& c : m_Components) c->OnUpdate(deltatime);
	}
	void Entity::OnDraw()
	{
		for (auto& c : m_Components) c->OnDraw();
	}

	// Entity List
	void EntityList::OnUpdate(float deltatime)
	{
		for (auto& e : m_Entities) e->OnUpdate(deltatime);
	}
	void EntityList::OnDraw()
	{
		for (auto& e : m_Entities) e->OnDraw();
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

}