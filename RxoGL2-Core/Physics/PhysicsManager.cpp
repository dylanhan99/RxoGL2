#include "PhysicsManager.h"
#include "../ECS/StandardComponents.h"
#include <gtx/perpendicular.hpp>

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
				//first->OnCollisionEnter(second);
				//second->OnCollisionEnter(first);
			}
		}
	}

	for (auto pair : m_CollidablesColliding)
	{
		auto first = pair.first;
		auto second = pair.second;
		if (first->CheckCollision(second))
		{
			//first->OnCollisionStay(second);
			//second->OnCollisionStay(first);
			continue;
		}
		first->IsColliding(false);
		second->IsColliding(false);
		//first->OnCollisionExit(second);
		//second->OnCollisionExit(first);
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

bool PhysicsManager::PolyPoly(ECS::sPtrPolygonCollider c1, ECS::sPtrPolygonCollider c2)
{
	auto& c1PerpPlanes = c1->GetPlanes();
	for (const auto& plane : c1PerpPlanes)
	{
		auto c1Range = c1->Project(plane);
		auto c2Range = c2->Project(plane);

		if ((c1Range.first < c2Range.second && c1Range.first > c2Range.second) ||
			(c2Range.first < c1Range.second && c2Range.first > c1Range.second))
			continue;
		else
			return false;
	}
	return true;
}

bool PhysicsManager::CircleCircle(ECS::sPtrCircleCollider c1, ECS::sPtrCircleCollider c2)
{
	if (glm::distance(c1->GetPosition(), c2->GetPosition()) < (c1->GetRadius() + c2->GetRadius()))
		return true;
	return false;
}

bool PhysicsManager::PolyCircle(ECS::sPtrPolygonCollider c1, ECS::sPtrCircleCollider c2)
{
	auto& c1PerpPlanes = c1->GetPlanes();
	for (const auto& plane : c1PerpPlanes)
	{
		auto polyRange = c1->Project(plane);
		auto circRange = c2->Project(plane);

		if ((polyRange.first < circRange.second && polyRange.first > circRange.second) ||
			(circRange.first < polyRange.second && circRange.first > polyRange.second))
			continue;
		else
			return false;
	}
	return true;
}