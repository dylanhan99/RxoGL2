#include "MainScene.h"
#include <ext.hpp>
#include <glm.hpp>

MainScene::MainScene()
	: s1("../res/Shaders/basicVert.shader", "../res/Shaders/basicFrag.shader"), 
	l1(s1, glm::ortho(0.f, 960.f, 0.f, 540.f, -200.0f, 200.0f))
{
	e1.AddComponent<ECS::Transform>(0, 0, 0);
	e1.AddComponent<ECS::Sprite>(1.f, 1.f, 1.f, 1.f);

	l1.Add(e1);
	AddLayer(l1);
}

MainScene::~MainScene()
{

}

void MainScene::OnUpdate(float deltatime)
{

}

void MainScene::OnRender()
{

}

void MainScene::OnImguiRender()
{

}