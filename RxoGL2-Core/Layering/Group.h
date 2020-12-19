#pragma once
#include "../ECS/ECS.h"

namespace ECS 
{
	class Group : public Entity
	{
	private:
		ECS::sPtrEntityList m_EntityList;
		glm::mat4 m_TransformationMatrix;
	public:
		Group(const glm::mat4& transform);
		ECS::sPtrEntity Add(Entity& entity);

		void OnAwake() override;
		void OnStart() override;
		void OnStop() override;
		void OnUpdate(float deltatime) override;
		void OnDraw() override;
	};

}