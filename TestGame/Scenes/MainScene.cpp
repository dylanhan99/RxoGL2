#include "MainScene.h"
#include <ext.hpp>
#include <glm.hpp>

#include "Vendor/imgui-single.h"

#include "../Scripts/CameraOrthoController.h"

MainScene::MainScene()
	: s1("../res/Shaders/basicVert.shader", "../res/Shaders/basicFrag.shader"), 
	l1(s1, glm::ortho(0.f, 960.f, 0.f, 540.f, -200.0f, 200.0f))
{
	l1.Add(camera);
	l1.Add(e1);
	AddLayer(l1);

	camera.AddComponent<ECS::NativeScriptComponent>()->Bind<CameraOrthoController, float>(960.f / 540.f);

	e1.AddComponent<ECS::Transform>(0, 0, 0)->SetSize(200.f, 200.f);
	e1.AddComponent<ECS::Sprite>(1.f, 1.f, 0.5f, 1.f);

	s1.Bind();
	int texIDs[32];
	for (int i = 0; i < 32; i++)
		texIDs[i] = i;
	s1.SetUniform1iv("u_Textures", 32, texIDs);
}

MainScene::~MainScene()
{

}

//void MainScene::OnStart()
//{
//
//}
//
//void MainScene::OnStop()
//{
//
//}
//
//void MainScene::OnUpdate(float deltatime)
//{
//
//}
//
//void MainScene::OnRender()
//{
//
//}
//
void MainScene::OnImguiRender()
{
	Scene::OnImguiRender();
	ImGui::SliderFloat3("Trans x", &(e1.GetComponent<ECS::Transform>()->GetPosition().x), -100.0f, 100.0f);
}