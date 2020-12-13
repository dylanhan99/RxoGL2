#pragma once
#include "../ECS/ECS.h"

class Layer
{
protected:
	sPtrBatchRenderer2D m_Renderer;
	sPtrShader m_Shader;
	glm::mat4 m_ProjectionMatrix;
	ECS::sPtrEntityList m_EntityList;
	sPtrLayer m_sPtrThis;

	std::vector<ECS::sPtrNativeScriptComponent> m_Scripts;
public:
	Layer(/*BatchRenderer2D& renderer, */Shader& shader, glm::mat4 matrix);
	virtual ~Layer();
	virtual void OnPlay() { for (auto s : m_Scripts) { s->InstantiateFunction(); s->OnCreateFunction(); } }// = 0;
	virtual void OnStop(){}// = 0;
	virtual void OnUpdate(float deltatime);
	virtual void OnRender();
	virtual ECS::sPtrEntity Add(ECS::Entity& entity);

	// Getters/Setters
	inline const sPtrBatchRenderer2D	GetRenderer()	const { return m_Renderer; }
	inline const sPtrShader				GetShader()	const { return m_Shader; }
	inline std::vector<ECS::sPtrEntity> GetEntitiesTag(std::string tag) { return m_EntityList->GetEntitiesTag(tag); }
	inline const std::vector<ECS::sPtrNativeScriptComponent> GetScripts() const { return m_Scripts; }
	inline void AddScript(ECS::sPtrNativeScriptComponent component) { m_Scripts.push_back(component); }
};