#include "Behaviour.h"
#pragma once

class EvadeBehaviour : public Behaviour
{
public:
	EvadeBehaviour() {}
	virtual ~EvadeBehaviour() {}

	virtual void update(Agent* agent, float deltaTime);
	void setTarget(Agent* agent) { m_target = agent; }
private:
	Agent* m_target = nullptr;
};