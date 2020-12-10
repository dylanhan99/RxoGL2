#include "Layer.h"
#include "../Graphics/Renderers/BatchRenderer.h"
#include "../Graphics/Shaders/Shader.h"

Layer::Layer(/*BatchRenderer2D& renderer, */Shader& shader, glm::mat4 matrix)
	: m_Renderer(std::make_shared<BatchRenderer2D>(/*renderer*/)), 
	m_Shader(std::make_shared<Shader>(shader)), 
	m_ProjectionMatrix(matrix), 
	m_EntityList(std::make_shared<ECS::EntityList>()), m_sPtrThis(this)
{
	
}

Layer::~Layer()
{
	//for (unsigned int i = 0; i < m_Renderables.size(); i++)
	//	delete m_Renderables[i];
	return;
}

void Layer::OnUpdate(float deltatime)
{
	m_EntityList->OnUpdate(deltatime);
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