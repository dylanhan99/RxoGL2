#include "MainScene.h"
#include <ext.hpp>
#include <glm.hpp>

#include "Vendor/imgui-single.h"
#include "Singletons/FontCache.h"
#include "../Scripts/CameraOrthoController.h"

MainScene::MainScene()
	: s1("../res/Shaders/basicVert.shader", "../res/Shaders/basicFrag.shader"), 
	l1(s1, glm::ortho(0.f, 960.f, 0.f, 540.f, -200.0f, 200.0f))
{
	Singletons::FontCache::Instance()->AddFont("arial", "../res/Fonts/arial.ttf");

	l1.Add(camera);
	//l1.Add(eSprite);
	l1.Add(eTexture);
	l1.Add(eTextureSheet);
	//l1.Add(eLabel);
	AddLayer(l1);

	camera.AddComponent<ECS::NativeScriptComponent>()->Bind<CameraOrthoController>(960.f / 540.f, true);

	eSprite.AddComponent<ECS::Transform>(0, 0, 0)->SetSize(50.f, 50.f);
	eSprite.AddComponent<ECS::Sprite>(1.f, 1.f, 0.5f, 1.f);

	std::vector<glm::vec3> colliderCoords;
	colliderCoords.push_back(glm::vec3(0.f, 0.f, 0.f));
	colliderCoords.push_back(glm::vec3(0.f, 1.f, 0.f));
	colliderCoords.push_back(glm::vec3(1.f, 1.f, 0.f));
	colliderCoords.push_back(glm::vec3(1.f, 0.f, 0.f));
	eTexture.AddComponent<ECS::Transform>(0, 0, 0)->SetSize(70.f, 70.f);
	eTexture.AddComponent<ECS::Sprite>("yo", "../res/Textures/yo2.png", 0.23f, 0.38f, 0.76f, 0.f);
	eTexture.AddComponent<ECS::PolygonCollider>(&(eSprite.GetComponent<ECS::Transform>()->GetPosition()), colliderCoords);

	eTextureSheet.AddComponent<ECS::Transform>(0, 0, 0)->SetSize(40.f, 50.f);
	eTextureSheet.AddComponent<ECS::Sprite>("yo1", "../res/Textures/yo1.png", 0.f, 0.f, 0.f, 1.f, true)->Add("yo1", 8.f, 8.f, 8.f, 8.f);
	eTextureSheet.AddComponent<ECS::PolygonCollider>(&(eTextureSheet.GetComponent<ECS::Transform>()->GetPosition()), colliderCoords);

	eLabel.AddComponent<ECS::Transform>(0, 0, 0);
	eLabel.AddComponent<ECS::Label>("TriHard", "arial", 1.f);

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
	ImGui::SliderFloat3("Trans x", &(eSprite.GetComponent<ECS::Transform>()->GetPosition().x), -100.0f, 100.0f);
}