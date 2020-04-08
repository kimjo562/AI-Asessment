#include "Decision.h"
#pragma once

class BehaviourDecision : public Decision
{
public:
	BehaviourDecision(Behaviour* behaviour) : m_behaviour(behaviour) {}
	~BehaviourDecision() {}

	virtual void makeDecision(Agent* agent, float deltaTime);

private:
	Behaviour* m_behaviour = nullptr;
};

