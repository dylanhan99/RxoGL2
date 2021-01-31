#include "Application.h"
#include "Layering/Scene.h"

#include "Scenes/MainScene.h"
#include "Utils/Timer.h"

int main()
{
	auto App = Application::Instance();
	App->GetSceneMenu()->RegisterScene<MainScene>("MainScene");
	App->GetSceneMenu()->LoadScene("MainScene");

	App->ApplicationLoop();
	return 0;
}