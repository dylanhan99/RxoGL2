#include "Window.h"

void window_resize_callback(GLFWwindow* window, int width, int height);

Window::Window(std::string title, int width, int height)
	: m_Title(title), m_Width(width), m_Height(height), 
	m_Minimized(false)
{
	if (!Init())
	{ this->~Window(); }
}

Window::~Window() 
{ 
	glfwTerminate(); 
}

bool Window::Init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to create GLFW!" << std::endl;
		return false;
	}
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
	if (!m_Window)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowSizeCallback(m_Window, window_resize_callback);

	glfwSwapInterval(0.f);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW!" << std::endl;
		return false;
	}
	return true;
}

bool Window::Closed()
{
	return glfwWindowShouldClose(m_Window);
}

void Window::OnUpdate() const
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Window::SetViewPort(int& width, int& height)
{
	glViewport(0, 0, width, height);
}

void window_resize_callback(GLFWwindow* window, int width, int height)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	if (width <= 0 || height <= 0)
	{
		win->m_Minimized = true;
		return;
	}
	win->m_Minimized = false;
	win->SetViewPort(width, height);
	// All functions subscribed to the RX_EVENT_WINDOWRESIZE event are called
	//Events::EventDispatcher::GetInstance()->DispatchEvent(RX_EVENT_WINDOWRESIZE, (float&)width, (float&)height);
}