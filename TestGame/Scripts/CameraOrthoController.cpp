#include "CameraOrthoController.h"
#include <ext.hpp>

#include "ECS/ECS.h"
#include "Layering/Layer.h"
#include "Graphics/Shaders/Shader.h"

#include "Singletons/EventCache.h"

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
	m_Camera.SetPos(CameraPosition());
	m_Camera.SetRotation(CameraRotation());
	const glm::mat4& pv = m_Camera.GetProjViewMat();
	{
		m_Entity->Layer()->GetShader()->Bind();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3());
		glm::mat4 mvp = pv * model;
		m_Entity->Layer()->GetShader()->SetUniformMat4f("u_MVP", mvp);
	}
}