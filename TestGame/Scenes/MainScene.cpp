#include "MainScene.h"
#include <ext.hpp>
#include <glm.hpp>

#include "Vendor/imgui-single.h"
#include "Singletons/FontCache.h"
#include "../Scripts/CameraOrthoController.h"
#include "../Scripts/PlayerController.h"

MainScene::MainScene()
	: s1("../res/Shaders/basicVert.shader", "../res/Shaders/basicFrag.shader"), 
	l1(s1, glm::ortho(0.f, 960.f, 0.f, 540.f, -200.0f, 200.0f))
{
	Singletons::FontCache::Instance()->AddFont("arial", "../res/Fonts/arial.ttf");

	eCamera = ECS::Entity("CameraOrtho");
	ePlayer = ECS::Entity("Player");
	l1.Add(eCamera);
	l1.Add(eGround);
	l1.Add(ePlayer);
	AddLayer(l1);

	std::vector<glm::vec3> colliderCoords;
	colliderCoords.push_back(glm::vec3(0.f, 0.f, 0.f));
	colliderCoords.push_back(glm::vec3(0.f, 1.f, 0.f));
	colliderCoords.push_back(glm::vec3(1.f, 1.f, 0.f));
	colliderCoords.push_back(glm::vec3(1.f, 0.f, 0.f));

	eCamera.AddComponent<CameraOrthoController>(960.f / 540.f, true);

	ePlayer.AddComponent<ECS::Transform>(0, 0, 0)->SetSize(10.f, 10.f);
	ePlayer.AddComponent<ECS::Sprite>("player", "../res/Textures/player.png", 0.23f, 0.38f, 0.76f, 0.f);
	ePlayer.AddComponent<ECS::PolygonCollider>(&(ePlayer.GetComponent<ECS::Transform>()->GetPosition()), colliderCoords)->SetPType(ECS::CollidableComponent::pType::Dynamic);
	ePlayer.AddComponent<PlayerController>();

	eGround.AddComponent<ECS::Transform>(0, 0, 0)->SetSize(50.f, 50.f);
	eGround.AddComponent<ECS::Sprite>("ground", "../res/Textures/dirt.png", 0.23f, 0.38f, 0.76f, 0.f);
	eGround.AddComponent<ECS::PolygonCollider>(&(eGround.GetComponent<ECS::Transform>()->GetPosition()), colliderCoords)->SetPType(ECS::CollidableComponent::pType::Static);

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
	//ImGui::SliderFloat3("Trans x", &(eSprite.GetComponent<ECS::Transform>()->GetPosition().x), -100.0f, 100.0f);
}