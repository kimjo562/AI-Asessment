#include "Behaviour.h"
#pragma once

class StatBehaviour : public Behaviour
{
public:
	StatBehaviour() {}
	virtual ~StatBehaviour() {}

	virtual void update(Agent* agent, float deltaTime);
	void setTarget(Agent* agent) { m_target = agent; }

private:
	Agent* m_target = nullptr;
};

