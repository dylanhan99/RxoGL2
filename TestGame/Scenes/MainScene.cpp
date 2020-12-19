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

	//const float ratio = 1080 / 960;
	camera.AddComponent<ECS::NativeScriptComponent>()->Bind<CameraOrthoController>(1080/960);

	e1.AddComponent<ECS::Transform>(0, 0, 0)->SetSize(20.f, 20.f);
	e1.AddComponent<ECS::Sprite>(1.f, 1.f, 0.5f, 1.f);
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