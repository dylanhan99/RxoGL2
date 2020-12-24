#pragma once
#include "../../Constants.h"

class CameraOrtho
{
private:
	glm::mat4 m_ProjMat;
	glm::mat4 m_ViewMat;
	glm::mat4 m_ProjViewMat;
	glm::vec3 m_Pos;
	float m_Rotation; // Degrees

public:
	CameraOrtho() {};
	CameraOrtho(float left, float right, float bottom, float top);
	~CameraOrtho();

	void CalcViewMat();

	// Getters/Setters
	inline const glm::mat4& GetProjMat()		const { return m_ProjMat; }
				 void		SetProjMat(float left, float right, float bottom, float top);
	inline const glm::mat4& GetViewMat()		const { return m_ViewMat; }
	inline const glm::mat4& GetProjViewMat()	const { return m_ProjViewMat; }
	inline const glm::vec3& GetPos()			const { return m_Pos; }
	inline		 void		SetPos(float& x, float& y, float& z)	{ m_Pos = { x, y, z };  CalcViewMat(); }
	inline		 void		SetPos(glm::vec3& newPos)				{ m_Pos = newPos;		CalcViewMat(); }
	inline		 void		SetRotation(float& rotation)			{ m_Rotation = rotation;  CalcViewMat(); }
};