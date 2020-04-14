#include "State.h"
#include "Agent.h"
#pragma once

class HungerState : public State
{
public:
	HungerState(Agent* target, float speed) : m_target(target), m_speed(speed) {}
	virtual ~HungerState() {}

	virtual void update(Agent* agent, float deltaTime);
	void setTarget(Agent* agent) { m_target = agent; }

private:
	Agent*	m_target;
	float	m_speed;
};