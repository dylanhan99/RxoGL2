#pragma once
#include "Graphics/Shaders/Shader.h"
#include "Layering/Scene.h"
#include "Layering/Layer.h"
#include "ECS/ECS.h"
#include "ECS/StandardComponents.h"

class MainScene : public Scene
{
private:
	Shader s1;

	Layer l1;
	ECS::Entity eCamera, ePlayer;
	ECS::Entity eRed, eBlue, eGreen;
	ECS::Entity eGround;

public:
	MainScene();
	~MainScene();

	//void OnAwake() override;
	//void OnStart() override;
	//void OnStop() override;
	//void OnUpdate(float deltatime) override;
	//void OnRender() override;
	void OnImguiRender() override;
};