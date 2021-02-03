#pragma once
#include "../Constants.h"

#include <unordered_set>

struct ComponentPairHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        std::size_t x = t.first->Entity()->ID();
        std::size_t y = t.second->Entity()->ID();

        return (x >= y) ? (x * x + x + y) : (y * y + y + x);
    }
};

class PhysicsManager
{
private:
	typedef std::pair<ECS::sPtrCollidableComponent, ECS::sPtrCollidableComponent> CollidableComponentPair;
	std::vector<ECS::sPtrCollidableComponent> m_Collidables;
    std::unordered_set<CollidableComponentPair, ComponentPairHash> m_CollidablesColliding;
public:
	void OnUpdate(float deltatime);
    void Add(ECS::sPtrCollidableComponent component);

    static bool PolyPoly(ECS::sPtrPolygonCollider c1, ECS::sPtrPolygonCollider c2);
    static bool CircleCircle(ECS::sPtrCircleCollider c1, ECS::sPtrCircleCollider c2);
    static bool PolyCircle(ECS::sPtrPolygonCollider c1, ECS::sPtrCircleCollider c2);
};