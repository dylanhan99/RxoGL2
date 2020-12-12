#include "Window.h"
#include "Singletons/EventCache.h"

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback			 (GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback	 (GLFWwindow* window, int button, int action, int mods);
void scroll_callback		 (GLFWwindow* window, double xOffset, double yOffset);
void window_resize_callback	 (GLFWwindow* window, int width, int height);

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
	glfwSetWindowUserPointer	(m_Window, this);
	glfwSetCursorPosCallback	(m_Window, cursor_position_callback);
	glfwSetKeyCallback			(m_Window, key_callback);
	glfwSetMouseButtonCallback	(m_Window, mouse_button_callback);
	glfwSetScrollCallback		(m_Window, scroll_callback);
	glfwSetWindowSizeCallback	(m_Window, window_resize_callback);

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

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	//Window* win = (Window*)glfwGetWindowUserPointer(window);
	//win->mx = xpos;
	//win->my = ypos;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Window* win = (Window*)glfwGetWindowUserPointer(window);
	//win->m_Keys[key] = action != GLFW_RELEASE;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//Window* win = (Window*)glfwGetWindowUserPointer(window);
	//win->m_MouseButtons[button] = action != GLFW_RELEASE;
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	Singletons::EventDispatcher::Instance()->DispatchEvent(EVENT_NAME_SCROLLWHEEL, (int)xOffset, (int)yOffset);
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