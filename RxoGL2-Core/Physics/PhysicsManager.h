#pragma once
#include "../MonoBehaviour.h"

#include <unordered_set>

struct ComponentPairHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        std::size_t x = t.first->Entity()->ID();
        std::size_t y = t.second->Entity()->ID();
        return Hash(x, y);
    }

    static inline std::size_t Hash(std::size_t x, std::size_t y) { return (x >= y) ? (x * x + x + y) : (y * y + y + x); }
};

class PhysicsManager : public MonoBehaviour
{
private:
	typedef std::pair<ECS::sPtrCollidableComponent, ECS::sPtrCollidableComponent> CollidableComponentPair;
	std::vector<ECS::sPtrCollidableComponent> m_Collidables;
    std::unordered_set<CollidableComponentPair, ComponentPairHash> m_CollidablesColliding;
public:
	void OnUpdate(float deltatime) override;
    void CollisionUpdate();
    void PhysicsUpdate(float deltatime);
    void InteractionUpdate(float deltatime);
    void Add(ECS::sPtrCollidableComponent component);

    // Collision Types
    static bool PolyPoly(ECS::sPtrPolygonCollider c1, ECS::sPtrPolygonCollider c2);
    static bool CircleCircle(ECS::sPtrCircleCollider c1, ECS::sPtrCircleCollider c2);
    static bool PolyCircle(ECS::sPtrPolygonCollider c1, ECS::sPtrCircleCollider c2);

    // Physics Types
    static void Static(ECS::sPtrCollidableComponent c);
    static void Kinematic(ECS::sPtrCollidableComponent c);
    static void Dynamic(ECS::sPtrCollidableComponent c);

    // Interaction Types
    static void StaticKinematic(ECS::sPtrCollidableComponent c1, ECS::sPtrCollidableComponent c2);
    static void StaticDynamic(ECS::sPtrCollidableComponent c1, ECS::sPtrCollidableComponent c2);
    static void KinematicDynamic(ECS::sPtrCollidableComponent c1, ECS::sPtrCollidableComponent c2);
    static void KinematicKinematic(ECS::sPtrCollidableComponent c1, ECS::sPtrCollidableComponent c2);
    static void DynamicDynamic(ECS::sPtrCollidableComponent c1, ECS::sPtrCollidableComponent c2);
};