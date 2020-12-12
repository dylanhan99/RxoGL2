#include "MainScene.h"
#include <ext.hpp>
#include <glm.hpp>

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
	e1.AddComponent<ECS::Transform>(0, 0, 0);
	e1.AddComponent<ECS::Sprite>(1.f, 1.f, 1.f, 1.f);
}

MainScene::~MainScene()
{

}

void MainScene::OnUpdate(float deltatime)
{
	Scene::OnUpdate(deltatime);
}

void MainScene::OnRender()
{
	Scene::OnRender();
}

void MainScene::OnImguiRender()
{
	
}