#pragma once
#include "Graphics/Cameras/CameraOrtho.h"
#include "ECS/ECS.h"

class CameraOrthoController : public ECS::NativeScript
{
private:
	static CameraOrtho m_Camera;
	static float m_AspectRatio;
	static float m_ZoomLevel;

	bool m_IsRotating;
	glm::vec3	m_CameraPosition;
	float		m_CameraRotation; //In degrees, anti-clockwise direction
	float		m_CameraTranslationSpeed;
	float		m_CameraRotationSpeed;
public:
	CameraOrthoController(const float& aspectRatio, bool rotation = false);
	~CameraOrthoController();

	void OnAwake() override;
	void OnStart() override;
	void OnStop() override;
	void OnUpdate(float deltatime) override;

	// Events
	static void OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjMat(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
	static void OnMouseScrolled(int xOffset, int yOffset)
	{
		m_ZoomLevel -= yOffset * 5.f;
		//m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjMat(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
};