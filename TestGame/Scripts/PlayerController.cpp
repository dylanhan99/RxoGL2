#include "PlayerController.h"

#include "Layering/Layer.h"
#include "Singletons/InputModule.h"

void PlayerController::OnAwake()
{

}

void PlayerController::OnStart()
{
	m_CameraOrtho = m_Entity->Layer()->GetEntity("CameraOrtho")->GetComponent<CameraOrthoController>();
}

void PlayerController::OnStop()
{

}

void PlayerController::OnUpdate(float deltatime)
{
	if (Input::GetKeyDown(GLFW_KEY_D))
	{
		m_CameraOrtho->CameraPosition(
			m_CameraOrtho->CameraPosition().x - cos(glm::radians(m_CameraOrtho->CameraRotation())) * m_CameraOrtho->CameraTranslationSpeed() * deltatime,
			m_CameraOrtho->CameraPosition().y - sin(glm::radians(m_CameraOrtho->CameraRotation())) * m_CameraOrtho->CameraTranslationSpeed() * deltatime,
			m_CameraOrtho->CameraPosition().z
		);
	}
	if (Input::GetKeyDown(GLFW_KEY_A))
	{
		m_CameraOrtho->CameraPosition(
			m_CameraOrtho->CameraPosition().x + cos(glm::radians(m_CameraOrtho->CameraRotation())) * m_CameraOrtho->CameraTranslationSpeed() * deltatime,
			m_CameraOrtho->CameraPosition().y + sin(glm::radians(m_CameraOrtho->CameraRotation())) * m_CameraOrtho->CameraTranslationSpeed() * deltatime,
			m_CameraOrtho->CameraPosition().z
		);
	}

	if (Input::GetKeyDown(GLFW_KEY_S))
	{
		m_CameraOrtho->CameraPosition(
			m_CameraOrtho->CameraPosition().x + -sin(glm::radians(m_CameraOrtho->CameraRotation())) * m_CameraOrtho->CameraTranslationSpeed() * deltatime,
			m_CameraOrtho->CameraPosition().y + cos(glm::radians(m_CameraOrtho->CameraRotation())) * m_CameraOrtho->CameraTranslationSpeed() * deltatime,
			m_CameraOrtho->CameraPosition().z
		);
	}
	if (Input::GetKeyDown(GLFW_KEY_W))
	{
		m_CameraOrtho->CameraPosition(
			m_CameraOrtho->CameraPosition().x - -sin(glm::radians(m_CameraOrtho->CameraRotation())) * m_CameraOrtho->CameraTranslationSpeed() * deltatime,
			m_CameraOrtho->CameraPosition().y - cos(glm::radians(m_CameraOrtho->CameraRotation())) * m_CameraOrtho->CameraTranslationSpeed() * deltatime,
			m_CameraOrtho->CameraPosition().z
		);
	}

	if (m_CameraOrtho->IsRotating())
	{
		if (Input::GetKeyDown(GLFW_KEY_Q))
			m_CameraOrtho->CameraRotation(m_CameraOrtho->CameraRotation() + m_CameraOrtho->CameraRotationSpeed() * deltatime);
		if (Input::GetKeyDown(GLFW_KEY_E))
			m_CameraOrtho->CameraRotation(m_CameraOrtho->CameraRotation() - m_CameraOrtho->CameraRotationSpeed() * deltatime);

		if (m_CameraOrtho->CameraRotation() > 180.0f)
			m_CameraOrtho->CameraRotation(m_CameraOrtho->CameraRotation() - 360.0f);
		else if (m_CameraOrtho->CameraRotation() <= -180.0f)
			m_CameraOrtho->CameraRotation(m_CameraOrtho->CameraRotation() + 360.0f);

	}
	//m_CameraOrtho->OnUpdate(deltatime);
}