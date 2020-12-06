#include "Layer.h"
#include "../Graphics/Renderers/BatchRenderer.h"
#include "../Graphics/Shaders/Shader.h"

Layer::Layer(sPtrBatchRenderer2D renderer, sPtrShader shader, glm::mat4 matrix)
	: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(matrix), m_sPtrThis(this)
{
	
}

Layer::~Layer()
{
	//for (unsigned int i = 0; i < m_Renderables.size(); i++)
	//	delete m_Renderables[i];
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

void Layer::Add(ECS::Entity* entity)
{
	m_EntityList->AddEntity(entity)->Layer() = m_sPtrThis;
}