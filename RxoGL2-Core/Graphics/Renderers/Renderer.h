#pragma once
#include <vector>
#include "../../Constants.h"

namespace ecs {
	class RenderableComponent;
}

class Renderer2D
{
protected:
	std::vector<glm::mat4> m_TransformationStack;
	const glm::mat4* m_TransformationStackBack;

	Renderer2D()
	{
		m_TransformationStack.push_back(glm::mat4(1.0f));
		m_TransformationStackBack = &m_TransformationStack.back();
	}
public:
	void Push(const glm::mat4& matrix, bool override = false)
	{
		if (override)
			m_TransformationStack.push_back(matrix);
		else
			m_TransformationStack.push_back(m_TransformationStack[m_TransformationStack.size() - 1] * matrix);
		m_TransformationStackBack = &m_TransformationStack.back();
	}

	void Pop()
	{
		// To avoid popping the identity matrix
		if (m_TransformationStack.size() > 1)
		{
			m_TransformationStack.pop_back();
			m_TransformationStackBack = &m_TransformationStack.back();
		}
	}

	virtual void Begin() {}
	virtual void Submit(const ECS::PtrSprite component) = 0;
	virtual void Submit(const ECS::PtrLabel component) = 0;
	virtual void Submit(const ECS::PtrCollidableComponent component) = 0;
	virtual void End() {}
	virtual void Flush() = 0;
};
