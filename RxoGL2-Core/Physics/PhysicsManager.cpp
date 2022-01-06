#include "PhysicsManager.h"
#include "../ECS/StandardComponents.h"
#include <gtx/perpendicular.hpp>

void PhysicsManager::OnUpdate(float deltatime)
{
	CollisionUpdate();
	PhysicsUpdate(deltatime);
	InteractionUpdate(deltatime);
}

void PhysicsManager::CollisionUpdate()
{
	for (int i = 0; i < m_Collidables.size(); i++)
	{
		auto first = m_Collidables[i];
		//if (first->IsColliding())
		//	continue;
		for (int j = i + 1; j < m_Collidables.size(); j++)
		{
			auto second = m_Collidables[j];
			if (m_CollidablesColliding.find(std::make_pair(first, second)) != m_CollidablesColliding.end())
				continue;
			if (first->CheckCollision(second)) // if current component collides with component + 1
			{
				m_CollidablesColliding.emplace(std::make_pair(first, second));
				first->Entity()->OnCollisionEnter(second);
				second->Entity()->OnCollisionEnter(first);
				first->IsColliding(true);
				second->IsColliding(true);
			}
		}
	}

	for (auto pair : m_CollidablesColliding)
	{
		auto first = pair.first;
		auto second = pair.second;
		if (first->CheckCollision(second))
		{
			first->Entity()->OnCollisionStay(second);
			second->Entity()->OnCollisionStay(first);
			continue;
		}
		first->IsColliding(false);
		second->IsColliding(false);
		first->Entity()->OnCollisionExit(second);
		second->Entity()->OnCollisionExit(first);
		m_CollidablesColliding.erase(pair);
	}
}

void PhysicsManager::PhysicsUpdate(float deltatime)
{
	for (auto c : m_Collidables)
	{
		switch (c->GetPType())
		{
			case ECS::CollidableComponent::pType::Static:
				Static(c);
				continue;
			case ECS::CollidableComponent::pType::Kinematic:
				Kinematic(c);
				continue;
			case ECS::CollidableComponent::pType::Dynamic:
				Dynamic(c);
				continue;
			default:
				continue;
		}
	}
}

void PhysicsManager::InteractionUpdate(float deltatime)
{
	for (auto p : m_CollidablesColliding)
	{
		// Check isTrigger whatever thing here. Then call OnCol/OnTrigger respectively.
		switch (p.first->GetPType())
		{
		case ECS::CollidableComponent::pType::Static:
			switch (p.second->GetPType())
			{
				case ECS::CollidableComponent::pType::Static:
					continue;
				case ECS::CollidableComponent::pType::Kinematic:
					StaticKinematic(p.first, p.second);
					continue;
				case ECS::CollidableComponent::pType::Dynamic:
					StaticDynamic(p.first, p.second);
					continue;
				default:
					continue;
			}
			continue;

		case ECS::CollidableComponent::pType::Kinematic:
			switch (p.second->GetPType())
			{
			case ECS::CollidableComponent::pType::Static:
				StaticKinematic(p.second, p.first);
				continue;
			case ECS::CollidableComponent::pType::Kinematic:
				KinematicKinematic(p.first, p.second);
				continue;
			case ECS::CollidableComponent::pType::Dynamic:
				KinematicDynamic(p.first, p.second);
				continue;
			default:
				continue;
			}
			continue;

		case ECS::CollidableComponent::pType::Dynamic:
			switch (p.second->GetPType())
			{
			case ECS::CollidableComponent::pType::Static:
				StaticDynamic(p.second, p.first);
				continue;
			case ECS::CollidableComponent::pType::Kinematic:
				KinematicDynamic(p.first, p.second);
				continue;
			case ECS::CollidableComponent::pType::Dynamic:
				DynamicDynamic(p.first, p.second);
				continue;
			default:
				continue;
			}
			continue;
		default:
			continue;
		}
	}
}

void PhysicsManager::Add(ECS::sPtrCollidableComponent component)
{
	m_Collidables.push_back(component);
}

// Collision Types
bool PhysicsManager::PolyPoly(ECS::sPtrPolygonCollider c1, ECS::sPtrPolygonCollider c2)
{
	auto& c1PerpPlanes = c1->GetPlanes();
	for (const auto& plane : c1PerpPlanes)
	{
		auto c1Range = c1->Project(plane);
		auto c2Range = c2->Project(plane);

		if (c1Range.first <= c2Range.second && c1Range.second >= c2Range.first)/* ||
			(c2Range.first < c1Range.second && c2Range.first > c1Range.second))*/
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

// Physics Types
void PhysicsManager::Static(ECS::sPtrCollidableComponent c)
{
	
}

void PhysicsManager::Kinematic(ECS::sPtrCollidableComponent c)
{
	
}

void PhysicsManager::Dynamic(ECS::sPtrCollidableComponent c)
{
	
}

// Interaction Types
void PhysicsManager::StaticKinematic(ECS::sPtrCollidableComponent c1, ECS::sPtrCollidableComponent c2)
{
	std::cout << "S - K" << std::endl;
}

void PhysicsManager::StaticDynamic(ECS::sPtrCollidableComponent c1, ECS::sPtrCollidableComponent c2)
{
	//if (c2->IsColliding())
	//{
		std::cout << "S - D" << std::endl;
		//c2->GetPosition().x = 
	//}
}

void PhysicsManager::KinematicDynamic(ECS::sPtrCollidableComponent c1, ECS::sPtrCollidableComponent c2)
{
	std::cout << "K - D" << std::endl;
}

void PhysicsManager::KinematicKinematic(ECS::sPtrCollidableComponent c1, ECS::sPtrCollidableComponent c2)
{
	std::cout << "K - K" << std::endl;
}

void PhysicsManager::DynamicDynamic(ECS::sPtrCollidableComponent c1, ECS::sPtrCollidableComponent c2)
{
	std::cout << "D - D" << std::endl;
}