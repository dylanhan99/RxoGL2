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
	l1.Add(eSprite);
	l1.Add(eLabel);
	l1.Add(eTexture);
	l1.Add(eTextureSheet);
	AddLayer(l1);

	camera.AddComponent<ECS::NativeScriptComponent>()->Bind<CameraOrthoController, float>(960.f / 540.f);

	eSprite.AddComponent<ECS::Transform>(0, 0, 0)->SetSize(50.f, 50.f);
	eSprite.AddComponent<ECS::Sprite>(1.f, 1.f, 0.5f, 1.f);

	eLabel.AddComponent<ECS::Transform>(0, 0, 0);
	eLabel.AddComponent<ECS::Label>("TriHard", "arial");

	eTexture.AddComponent<ECS::Transform>(0, 0, 0)->SetSize(30.f, 30.f);
	eTexture.AddComponent<ECS::Sprite>("yo", "../res/Textures/yo.png", 1.f, 1.f, 1.f, 1.f);

	eTextureSheet.AddComponent<ECS::Transform>(0, 0, 0)->SetSize(10.f, 30.f);
	eTextureSheet.AddComponent<ECS::Sprite>("yoSheet", "../res/Textures/yo.png", 0.f, 0.f, 0.f, 1.f);// , true);

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