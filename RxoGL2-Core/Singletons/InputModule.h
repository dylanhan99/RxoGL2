#pragma once
// https://docs.unity3d.com/ScriptReference/Input.html
#include <vector>

#define MAX_KEYS	1024
#define MAX_BUTTONS 32
class Input
{
private:
	static std::vector<bool> allFalse(unsigned int count)
	{
		std::vector<bool> vec;
		for (int i = 0; i < count; i++)
			vec[i] = false;
		return vec;
	}
public:
	static const std::vector<bool> Keys;
	static const std::vector<bool> MouseButtons;
	static double mx, my;

	static bool GetButton(unsigned int button)
	{
		return false;
	}
	static bool GetButtonDown(unsigned int button)
	{
		if (button >= MAX_BUTTONS)
			return false;
		return MouseButtons[button];
	}
	static bool GetButtonUp(unsigned int button)
	{
		return false;
	}

	static bool GetMouseButton(unsigned int key)
	{
		if (key >= MAX_KEYS)
			return false;
		return Keys[key];
	}
	static bool GetMouseButtonDown(unsigned int key)
	{
		return false;
	}
	static bool GetMouseButtonUp(unsigned int key)
	{
		return false;
	}
};