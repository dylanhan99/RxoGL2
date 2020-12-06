#include "Application.h"
#include "Vendor/imgui-single.h"
#include "Window.h"
#include "Graphics/Shaders/Shader.h"
#include "Layering/Scene.h"

sPtrApplication Application::m_Instance = NULL;

Application::Application()
{
	Init();
	
	//m_Shader = std::make_shared<Shader>("../res/Shaders/basicVert.shader", "../res/Shaders/basicFrag.shader");
	//float vertices[] = {
	//-0.5f, -0.5f, 0.0f,
	//-0.5f,  0.5f, 0.0f,
	// 0.5f,  0.5f, 0.0f//,
	// //0.5f, -0.5f, 0.0f
	//};
	//
	//m_Shader->Bind();
	//unsigned int vbo;
	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
}

Application::~Application()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Application::ApplicationLoop()
{
	float lastFrameTime = 0.f;
	while (!m_Window->Closed())
	{
		float time = (float)glfwGetTime(); // In seconds
		float dt = time - lastFrameTime; lastFrameTime = time;
		{
			OnUpdate((float)dt);
			//if(!m_Window->IsMinimized())
			OnRender();
			OnImguiRender();
		}
		m_Window->OnUpdate();
	}
}

void Application::Init()
{
	m_Window = std::make_shared<Window>("RxoGL-2", 960, 540);
	m_SceneMenu = std::make_unique<SceneMenu>(); // Have a default Scene be added somewhere...
	glClearColor(0.2f, 0.3f, 0.8f, 1.f);
	std::cout << glGetString(GL_VERSION) << std::endl;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Setting up imgui
	{
		// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		//io.Fonts->AddFontDefault();
		//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		//IM_ASSERT(font != NULL);
	}
}

void Application::OnUpdate(float deltatime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	
	if(m_SceneMenu->CurrentScene())
		m_SceneMenu->CurrentScene()->OnUpdate(deltatime);
}

void Application::OnRender()
{
	m_SceneMenu->CurrentScene()->OnRender();
}

void Application::OnImguiRender()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Scenes");

	m_SceneMenu->OnImguiRender();
	m_SceneMenu->CurrentScene()->OnImguiRender();

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}