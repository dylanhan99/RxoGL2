#pragma once
#include "../ECS/ECS.h"

class Layer
{
protected:
	sPtrBatchRenderer2D m_Renderer;
	sPtrShader m_Shader;
	ECS::sPtrEntityList m_EntityList;
	glm::mat4 m_ProjectionMatrix;
	sPtrLayer m_sPtrThis;

	Layer(sPtrBatchRenderer2D renderer, sPtrShader shader, glm::mat4 matrix);
public:
	virtual ~Layer();
	virtual void OnUpdate(float deltatime);
	virtual void OnRender();
	virtual void Add(ECS::Entity* entity);

	inline const sPtrBatchRenderer2D	Renderer()	const { return m_Renderer; }
	inline const sPtrShader				Shader()	const { return m_Shader; }
	inline std::vector<ECS::sPtrEntity> GetEntitiesTag(std::string tag) { return m_EntityList->GetEntitiesTag(tag); }
};