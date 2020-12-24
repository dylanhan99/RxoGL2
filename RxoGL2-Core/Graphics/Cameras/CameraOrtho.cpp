#include "CameraOrtho.h"
#include <ext.hpp>

CameraOrtho::CameraOrtho(float left, float right, float bottom, float top)
	: m_ViewMat(1.f),
	m_Pos({ 0.f, 0.f, 0.f }), m_Rotation(0.f)
{
	SetProjMat(left, right, bottom, top);
}

CameraOrtho::~CameraOrtho()
{

}

void CameraOrtho::CalcViewMat()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.f), m_Pos) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

	m_ViewMat = glm::inverse(transform);
	m_ProjViewMat = m_ProjMat * m_ViewMat;
}

void CameraOrtho::SetProjMat(float left, float right, float bottom, float top)
{
	m_ProjMat = glm::ortho(left, right, bottom, top, -1.f, 1.f);
	m_ProjViewMat = m_ProjMat * m_ViewMat;
}