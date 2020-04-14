#include "State.h"
#include "Agent.h"
#pragma once

class PredAtkState : public State
{
public:
	PredAtkState(Agent* target, float speed) : m_target(target), m_speed(speed) {}
	virtual ~PredAtkState() {}

	virtual void update(Agent* agent, float deltaTime);

private:
	Agent*	m_target;
	float	m_speed;
};