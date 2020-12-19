#include "Group.h"
#include "../ECS/ECS.h"

namespace ECS
{
	Group::Group(const glm::mat4& transform)
		: m_TransformationMatrix(transform),
		m_EntityList(std::make_shared<ECS::EntityList>())
	{

	}

	ECS::sPtrEntity Group::Add(Entity& entity)
	{
		return m_EntityList->AddEntity(entity);
	}

	void Group::OnAwake()
	{
		m_EntityList->OnAwake();
	}

	void Group::OnStart()
	{
		m_EntityList->OnStart();
	}

	void Group::OnStop()
	{
		m_EntityList->OnStop();
	}

	void Group::OnUpdate(float deltatime)
	{
		m_EntityList->OnUpdate(deltatime);
	}

	void Group::OnDraw()
	{
		m_EntityList->OnDraw();
	}
}