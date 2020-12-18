#include "Scene.h"
#include "Layer.h"
#include "../Vendor/imgui-single.h"

// Scene
void Scene::OnAwake()
{
	for (auto layer : m_Layers) layer->OnAwake();
}
void Scene::OnStart()
{
	for (auto layer : m_Layers) layer->OnStart();
}
void Scene::OnStop()
{
	for (auto layer : m_Layers) layer->OnStop();
}
void Scene::OnUpdate(float deltatime)
{
	for (auto layer : m_Layers) layer->OnUpdate(deltatime);
}
void Scene::OnRender()
{
	for (auto layer : m_Layers) layer->OnRender();
}
void Scene::OnImguiRender() 
{

}
sPtrLayer Scene::AddLayer(Layer& l)
{
	sPtrLayer sPtr{ &l };
	m_Layers.push_back(sPtr);
	return sPtr;
}

// Scene Menu
SceneMenu::SceneMenu()
{
	RegisterScene<Scene>("Sample Scene");
	LoadScene("Sample Scene");
}
SceneMenu::SceneMenu(Scene* currentScenePointer)
	: m_CurrentScene(currentScenePointer)
{

}
SceneMenu::~SceneMenu()
{
	//for (auto& test : m_Scenes)
	//	delete test.second();
}
void SceneMenu::OnImguiRender()
{
	for (auto& test : m_Scenes)
	{
		if (ImGui::Button(test.first.c_str()))
		{
			std::cout << "Loading '" << test.first << "'...\n";
			m_CurrentScene = test.second;
		}
	}
}