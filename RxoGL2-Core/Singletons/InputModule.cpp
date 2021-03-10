#include "InputModule.h"
glm::dvec2 Input::m_Cursor = glm::dvec2(0, 0);
std::vector<bool> Input::m_Keys			= Input::allFalse(MAX_KEYS);
std::vector<bool> Input::m_MouseButtons = Input::allFalse(MAX_BUTTONS);