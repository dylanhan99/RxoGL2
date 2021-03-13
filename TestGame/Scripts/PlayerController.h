#pragma once
#include "CameraOrthoController.h"

class PlayerController : public ECS::Component
{
private:
	ECS::sPtrTransform m_PlayerTransform;
	std::shared_ptr<CameraOrthoController> m_CameraOrtho;
public:
	void OnAwake() override;
	void OnStart() override;
	void OnStop() override;
	void OnUpdate(float deltatime) override;
};