#include "CameraOrthoController.h"
#include "Singletons/EventCache.h"

// Static variables used for OnEvent functions
float		CameraOrthoController::m_AspectRatio = NULL;
float		CameraOrthoController::m_ZoomLevel = 100.f;
CameraOrtho	CameraOrthoController::m_Camera = CameraOrtho();

CameraOrthoController::CameraOrthoController(float aspectRatio, bool isRotating)
	: m_IsRotating(isRotating),
	m_CameraPosition(0.f, 0.f, 0.f), m_CameraRotation(0.f), 
	m_CameraTranslationSpeed(40.f), m_CameraRotationSpeed(180.f)
{
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
}

void CameraOrthoController::OnStop()
{
	std::cout << "CameraOrthoController OnStop...\n";
}

void CameraOrthoController::OnUpdate(float deltatime)
{

}