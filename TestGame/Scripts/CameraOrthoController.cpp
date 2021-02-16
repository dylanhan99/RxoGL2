#include "CameraOrthoController.h"
#include <ext.hpp>

#include "Singletons/EventCache.h"
#include "ECS/ECS.h"
#include "Layering/Layer.h"
#include "Graphics/Shaders/Shader.h"

#include "Singletons/InputModule.h"

// Static variables used for OnEvent functions
CameraOrtho	CameraOrthoController::m_Camera = CameraOrtho();
float		CameraOrthoController::m_AspectRatio = NULL;
float		CameraOrthoController::m_ZoomLevel = 100.f;

CameraOrthoController::CameraOrthoController(const float& aspectRatio, bool isRotating)
	: m_IsRotating(isRotating),
	m_CameraPosition(0.f, 0.f, 0.f), m_CameraRotation(0.f), 
	m_CameraTranslationSpeed(40.f), m_CameraRotationSpeed(180.f)
{
	m_AspectRatio = aspectRatio;
	m_Camera = CameraOrtho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

	Singletons::EventDispatcher::Instance()->RegisterEvent(new Event::Event<float, float>(EVENT_NAME_WINDOWRESIZE, &OnResize));
	Singletons::EventDispatcher::Instance()->RegisterEvent(new Event::Event<int, int>(EVENT_NAME_SCROLLWHEEL, &OnMouseScrolled));
}

CameraOrthoController::~CameraOrthoController()
{

}

void CameraOrthoController::OnAwake()
{
	std::cout << "CameraOrthoController OnAwake...\n";
}

void CameraOrthoController::OnStart()
{
	std::cout << "CameraOrthoController OnStart...\n";

	m_Camera.SetPos(m_CameraPosition);
	m_Camera.SetRotation(m_CameraRotation);
}

void CameraOrthoController::OnStop()
{
	std::cout << "CameraOrthoController OnStop...\n";
}

void CameraOrthoController::OnUpdate(float deltatime)
{
	if (Input::GetKeyDown(GLFW_KEY_D))
	{
		m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
		m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
	}
	if (Input::GetKeyDown(GLFW_KEY_A))
	{
		m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
		m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
	}

	if (Input::GetKeyDown(GLFW_KEY_S))
	{
		m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
		m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
	}
	if (Input::GetKeyDown(GLFW_KEY_W))
	{
		m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
		m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
	}

	if (m_IsRotating)
	{
		if (Input::GetKeyDown(GLFW_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * deltatime;
		if (Input::GetKeyDown(GLFW_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * deltatime;

		if (m_CameraRotation > 180.0f)
			m_CameraRotation -= 360.0f;
		else if (m_CameraRotation <= -180.0f)
			m_CameraRotation += 360.0f;

	}
	m_Camera.SetPos(m_CameraPosition);
	m_Camera.SetRotation(m_CameraRotation);
	const glm::mat4& pv = m_Camera.GetProjViewMat();
	{
		m_Entity->Layer()->GetShader()->Bind();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3());
		glm::mat4 mvp = pv * model;
		m_Entity->Layer()->GetShader()->SetUniformMat4f("u_MVP", mvp);
	}
}