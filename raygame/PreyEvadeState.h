#include "State.h"
#include "Agent.h"
#pragma once

class PreyEvadeState : public State
{
public:
	PreyEvadeState(Agent* target, float speed) : m_target(target), m_speed(speed) {}
	virtual ~PreyEvadeState() {}

	virtual void update(Agent* agent, float deltaTime);
	void setTarget(Agent* agent) { m_target = agent; }

private:
	Agent*	m_target;
	float	m_speed;
};