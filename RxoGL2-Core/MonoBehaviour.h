#pragma once
#include "Constants.h"

class MonoBehaviour
{
public:
	virtual void OnAwake() {}
	virtual void OnStart() {}
	virtual void OnStop() {}
	virtual void OnUpdate(float deltatime) {}
	virtual void OnDraw() {}

	virtual void OnCollisionEnter(ECS::sPtrCollidableComponent component) {}
	virtual void OnCollisionStay(ECS::sPtrCollidableComponent component) {}
	virtual void OnCollisionExit(ECS::sPtrCollidableComponent component) {}
};