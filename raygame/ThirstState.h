#include "State.h"
#include "Agent.h"
#pragma once

class ThirstState : public State
{
public:
	ThirstState(Agent* target, float speed) : m_target(target), m_speed(speed) {}
	virtual ~ThirstState() {}

	virtual void update(Agent* agent, float deltaTime);
	void setTarget(Agent* agent) { m_target = agent; }

private:
	Agent*	m_target;
	float	m_speed;
};