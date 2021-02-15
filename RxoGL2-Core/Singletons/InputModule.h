#pragma once
// https://docs.unity3d.com/ScriptReference/Input.html
// https://gamedev.stackexchange.com/questions/150157/how-to-improve-my-input-handling-in-glfw
#include "../Constants.h"

#define MAX_KEYS	1024
#define MAX_BUTTONS 32
class Input
{
private:
	static glm::dvec2			m_Cursor;
	static std::vector<bool>	m_Keys;
	static std::vector<bool>	m_MouseButtons;
	static std::vector<bool> allFalse(unsigned int count)
	{
		std::vector<bool> vec;
		for (int i = 0; i < count; i++)
			vec.push_back(GLFW_RELEASE);
		return vec;
	}
public:
	// Cursor
	static const glm::dvec2 GetCursor()
	{
		return m_Cursor;
	}

	// Purely changing key state. (Down or Up)
	// These are ONLY called during key/button callback in Window.
	static void Keys(int key, int scancode, int action, int mods)
	{
		m_Keys[key] = action != GLFW_RELEASE;
	}
	static void Buttons(int button, int action, int mods)
	{
		m_MouseButtons[button] = action != GLFW_RELEASE;
	}
	static void Cursor(double xpos, double ypos)
	{
		m_Cursor.x = xpos;
		m_Cursor.y = ypos;
	}

	// Mouse
	static bool GetMouseDown(unsigned int button)
	{
		if (button >= MAX_BUTTONS || 
			m_MouseButtons[button] == GLFW_RELEASE)
			return false;
		return m_MouseButtons[button];
	}
	static bool GetMouseUp(unsigned int button)
	{
		if(button >= MAX_BUTTONS ||
			m_MouseButtons[button] != GLFW_RELEASE)
			return false;
		return m_MouseButtons[button];
	}

	// Keyboard
	static bool GetKeyDown(unsigned int key)
	{
		if (key >= MAX_BUTTONS ||
			m_Keys[key] == GLFW_RELEASE)
			return false;
		return m_Keys[key];
	}
	static bool GetKeyUp(unsigned int key)
	{
		if (key >= MAX_BUTTONS ||
			m_Keys[key] != GLFW_RELEASE)
			return false;
		return m_Keys[key];
	}
};