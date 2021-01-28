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

bool PhysicsManager::PolyPoly(ECS::sPtrPolygonCollider c1, ECS::sPtrPolygonCollider c2)
{
	
	return false;
}

bool PhysicsManager::CircleCircle(ECS::sPtrCircleCollider c1, ECS::sPtrCircleCollider c2)
{
	if (glm::distance(c1->GetPosition(), c2->GetPosition()) < (c1->GetRadius() + c2->GetRadius()))
		return true;
	return false;
}

bool PhysicsManager::PolyCircle(ECS::sPtrPolygonCollider c1, ECS::sPtrCircleCollider c2)
{
	auto& c1Points = c1->GetPoints();
	auto edge1 = c1Points[0] - c1Points[1];
	glm::vec3 perpPlaneOfEdge1(-edge1.y, edge1.x, edge1.z);
	/*
		Somehow get the minimum and maximum points relative to perpPlaneOfEdge1;
			This can be a function built into PolygonCollider.
			> Parse edge1 into std::pair<float, float> GetMinMax(glm::vec3 edge);
		Parse the two points into the glm::dot(a, b) function;
		Do the same for the circle.
		If the range overlaps, do second test.
		If not, return false.
	*/
	auto polyRange = c1->Project(edge1);
	auto circRange = c2->Project(edge1);
	if ((polyRange.first < circRange.second && polyRange.first > circRange.second) ||
		(circRange.first < polyRange.second && circRange.first > polyRange.second))
	{
		return true;
	}
	return false;
}