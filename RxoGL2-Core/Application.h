#pragma once
#include "Constants.h"

class Application
{
private:
	static sPtrApplication m_Instance;
	sPtrWindow m_Window;
	sPtrSceneMenu m_SceneMenu;
public:
	Application();
	~Application();
	static inline sPtrApplication Instance()
	{
		if (m_Instance == NULL)
			m_Instance = std::make_shared<Application>();
		return m_Instance;
	}
	void ApplicationLoop();

	// Getters/Setters
	inline const sPtrSceneMenu GetSceneMenu() const { return m_SceneMenu; }
private:
	void Init();
	void OnUpdate(float deltatime);
	void OnRender();
	void OnImguiRender();
};