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
	ECS::Entity e1;

public:
	MainScene();
	~MainScene();

	void OnUpdate(float deltatime) override;
	void OnRender() override;
	void OnImguiRender() override;
};