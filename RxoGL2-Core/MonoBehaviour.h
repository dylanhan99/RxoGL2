#pragma once

class MonoBehaviour
{
	virtual void OnAwake() {}
	virtual void OnStart() {}
	virtual void OnStop() {}
	virtual void OnUpdate(float deltatime) {}
	virtual void OnDraw() {}

	virtual void OnCollisionEnter() {}
	virtual void OnCollisionStay() {}
	virtual void OnCollisionExit() {}
};