#pragma once

#include <iostream>
#include "Constants.h"
class Window
{
private:
	RXOwindow* m_Window;

	std::string m_Title;
	int m_Width, m_Height;
	bool m_Minimized;
public:
	Window(std::string title, int width, int height);
	~Window();

	// Common
	bool Init();
	bool Closed();
	void OnUpdate() const;

	// Getters
	inline RXOwindow* GetWindow() { return m_Window; }

	// Misc
	void SetViewPort(int& width, int& height);
private:
	friend static void window_resize_callback(RXOwindow* window, int width, int height);
};