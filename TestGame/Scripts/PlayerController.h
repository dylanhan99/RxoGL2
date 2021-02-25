#pragma once
#include "CameraOrthoController.h"

class PlayerController : public ECS::NativeScript
{
private:
	ECS::sPtrTransform m_PlayerTransform;
	CameraOrthoController m_CameraOrtho;
public:
	void OnAwake() override;
	void OnStart() override;
	void OnStop() override;
	void OnUpdate(float deltatime) override;
};