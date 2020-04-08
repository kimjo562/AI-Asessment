#include "Behaviour.h"
#pragma once

class WanderBehaviour : public Behaviour
{
public:
	WanderBehaviour() {}
	virtual ~WanderBehaviour() {}

	virtual void update(Agent* agent, float deltaTime);

private:
	float m_radius = 500.0f;
	float m_offset = 0.0f;
	float m_jitter = 200.0f;
	Vector2 m_prevTarget = { 0, 0 };
};