#include "Layer.h"
#include "../Graphics/Renderers/BatchRenderer.h"
#include "../Graphics/Shaders/Shader.h"
#include "../Physics/PhysicsManager.h"

Layer::Layer(/*BatchRenderer2D& renderer, */Shader& shader, glm::mat4 matrix)
	: m_Renderer(std::make_shared<BatchRenderer2D>(/*renderer*/)), 
	m_Shader(std::make_shared<Shader>(shader)), 
	m_ProjectionMatrix(matrix), 
	m_EntityList(std::make_shared<ECS::EntityList>()), m_sPtrThis(this),
	m_PhysicsManager(std::make_shared<PhysicsManager>())
{
	
}

Layer::~Layer()
{
	//for (unsigned int i = 0; i < m_Renderables.size(); i++)
	//	delete m_Renderables[i];
}

void Layer::OnAwake()
{ 
	m_EntityList->OnAwake();
	//for (auto nsc : m_Scripts) 
	//{ 
	//	nsc->InstantiateFunction();
	//	nsc->Instance->OnAwake();
	//} 
}

void Layer::OnStart()
{ 
	m_EntityList->OnStart();
	//for (auto nsc : m_Scripts) nsc->Instance->OnStart();
}

void Layer::OnStop() 
{
	m_EntityList->OnStop();
	//for (auto nsc : m_Scripts) nsc->Instance->OnStop();
}

void Layer::OnUpdate(float deltatime)
{
	m_EntityList->OnUpdate(deltatime);
	m_PhysicsManager->OnUpdate(deltatime);
	//for (auto nsc : m_Scripts) nsc->Instance->OnUpdate(deltatime);
}

void Layer::OnRender()
{
	m_Shader->Bind();
	m_Renderer->Begin();
	m_EntityList->OnDraw();
	m_Renderer->End();
	m_Renderer->Flush();
}

ECS::sPtrEntity Layer::Add(ECS::Entity& entity)
{
	auto sPtr = m_EntityList->AddEntity(entity);
	sPtr->SetLayer(m_sPtrThis);
	return sPtr;
}

//void Layer::AddScript(ECS::sPtrNativeScriptComponent component)
//{
//	m_Scripts.push_back(component);
//}