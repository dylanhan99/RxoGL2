#pragma once
#include "Window.h"
#include "Graphics/Shaders/Shader.h"

class Application
{
private:
	static sPtrApplication m_Instance;
	sPtrWindow m_Window;
	sPtrShader m_Shader;
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
private:
	void Init();
	void OnUpdate(float deltatime);
	void OnRender();
	void OnImguiRender();
};