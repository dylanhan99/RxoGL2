#include "Application.h"
#include "Layering/Scene.h"

#include "Scenes/MainScene.h"


#include <gtx/perpendicular.hpp>
//#include "Physics/PhysicsManager.h"

int main()
{
	auto App = Application::Instance();
	App->GetSceneMenu()->RegisterScene<MainScene>("MainScene");
	App->GetSceneMenu()->LoadScene("MainScene");

	//{
	//	PhysicsManager yo;
	//	yo.OnUpdate(0.f);
	//}

	App->ApplicationLoop();
	return 0;
}