#include "PlayerController.h"

#include "Layering/Layer.h"
#include "Singletons/InputModule.h"
#include "ECS/StandardComponents.h"

void PlayerController::OnAwake()
{
	m_MovementSpd = 40.f;
}

void PlayerController::OnStart()
{
	m_CameraOrtho = m_Entity->Layer()->GetEntity("CameraOrtho")->GetComponent<CameraOrthoController>();
	m_PlayerTransform = m_Entity->GetComponent<ECS::Transform>();
}

void PlayerController::OnStop()
{

}

void PlayerController::OnUpdate(float deltatime)
{
	if (Input::GetKeyDown(GLFW_KEY_D))
	{
		m_PlayerTransform->SetPosition(
			m_PlayerTransform->GetPosition().x + cos(glm::radians(m_CameraOrtho->CameraRotation())) * m_MovementSpd * deltatime,
			m_PlayerTransform->GetPosition().y - sin(glm::radians(m_CameraOrtho->CameraRotation())) * m_MovementSpd * deltatime,
			m_PlayerTransform->GetPosition().z
		);
	}
	if (Input::GetKeyDown(GLFW_KEY_A))
	{
		m_PlayerTransform->SetPosition(
			m_PlayerTransform->GetPosition().x - cos(glm::radians(m_CameraOrtho->CameraRotation())) * m_MovementSpd * deltatime,
			m_PlayerTransform->GetPosition().y - sin(glm::radians(m_CameraOrtho->CameraRotation())) * m_MovementSpd * deltatime,
			m_PlayerTransform->GetPosition().z

		);
	}
	
	if (Input::GetKeyDown(GLFW_KEY_S))
	{
		m_PlayerTransform->SetPosition(
			m_PlayerTransform->GetPosition().x - -sin(glm::radians(m_CameraOrtho->CameraRotation())) * m_MovementSpd * deltatime,
			m_PlayerTransform->GetPosition().y - cos(glm::radians(m_CameraOrtho->CameraRotation())) * m_MovementSpd * deltatime,
			m_PlayerTransform->GetPosition().z
		);
	}
	if (Input::GetKeyDown(GLFW_KEY_W))
	{
		m_PlayerTransform->SetPosition(
			m_PlayerTransform->GetPosition().x + -sin(glm::radians(m_CameraOrtho->CameraRotation())) * m_MovementSpd * deltatime,
			m_PlayerTransform->GetPosition().y + cos(glm::radians(m_CameraOrtho->CameraRotation())) * m_MovementSpd * deltatime,
			m_PlayerTransform->GetPosition().z
		);
	}
	//
	//if (m_CameraOrtho->IsRotating())
	//{
	//	if (Input::GetKeyDown(GLFW_KEY_Q))
	//		m_CameraOrtho->CameraRotation(m_CameraOrtho->CameraRotation() + m_CameraOrtho->CameraRotationSpeed() * deltatime);
	//	if (Input::GetKeyDown(GLFW_KEY_E))
	//		m_CameraOrtho->CameraRotation(m_CameraOrtho->CameraRotation() - m_CameraOrtho->CameraRotationSpeed() * deltatime);
	//
	//	if (m_CameraOrtho->CameraRotation() > 180.0f)
	//		m_CameraOrtho->CameraRotation(m_CameraOrtho->CameraRotation() - 360.0f);
	//	else if (m_CameraOrtho->CameraRotation() <= -180.0f)
	//		m_CameraOrtho->CameraRotation(m_CameraOrtho->CameraRotation() + 360.0f);
	//
	//}
	//m_CameraOrtho->OnUpdate(deltatime);
	m_CameraOrtho->CameraPosition(m_PlayerTransform->GetPosition());
}