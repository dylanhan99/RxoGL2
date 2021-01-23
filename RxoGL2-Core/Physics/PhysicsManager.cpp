#include "PhysicsManager.h"
#include "../ECS/StandardComponents.h"

void PhysicsManager::OnUpdate(float deltatime)
{
	for (int i = 0; i < m_Collidables.size(); i++)
	{
		auto first = m_Collidables[i];
		if (first->IsColliding())
			continue;
		for (int j = i + 1; j < m_Collidables.size(); j++)
		{
			auto second = m_Collidables[j];
			if (first->CheckCollision(second)) // if current component collides with component + 1
			{
				first->IsColliding(true);
				second->IsColliding(true);
				m_CollidablesColliding.emplace(std::make_pair(first, second));
				first->OnCollisionEnter(second);
				second->OnCollisionEnter(first);
			}
		}
	}

	for (auto pair : m_CollidablesColliding)
	{
		auto first = pair.first;
		auto second = pair.second;
		if (first->CheckCollision(second))
		{
			first->OnCollisionStay(second);
			second->OnCollisionStay(first);
			continue;
		}
		first->IsColliding(false);
		second->IsColliding(false);
		first->OnCollisionExit(second);
		second->OnCollisionExit(first);
		m_CollidablesColliding.erase(pair);
	}
	//auto yo = std::make_pair(
	//	std::make_shared<ECS::CollidableComponent>(ECS::CollidableComponent()),
	//	std::make_shared<ECS::CollidableComponent>(ECS::CollidableComponent()));
	//m_CollidablesColliding.emplace(yo);
}

void PhysicsManager::Add(ECS::sPtrCollidableComponent component)
{
	m_Collidables.push_back(component);
}

bool PhysicsManager::BoxBox(ECS::sPtrBoxCollider c1, ECS::sPtrBoxCollider c2)
{
	if (c1->GetPosition().x						< c2->GetPosition().x + c2->GetSize().x &&
		c1->GetPosition().x + c1->GetSize().x	> c2->GetPosition().x					&&
		c1->GetPosition().y						< c2->GetPosition().y + c2->GetSize().y &&
		c1->GetPosition().y + c1->GetSize().y	> c2->GetPosition().y) 
		return true;
	return false;
}