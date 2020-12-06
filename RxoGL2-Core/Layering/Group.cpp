#include "Group.h"
#include "../ECS/ECS.h"

namespace ECS
{
	Group::Group(const glm::mat4& transform)
		: m_TransformationMatrix(transform)
	{

	}

	void Group::Add(Entity* entity)
	{
		m_EntityList->AddEntity(entity);
	}

	void Group::OnUpdate(float deltatime)
	{
		m_EntityList->OnUpdate(deltatime);
	}

	void Group::OnDraw()
	{

	}
}