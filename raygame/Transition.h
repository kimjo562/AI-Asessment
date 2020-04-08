#include "Agent.h"
#include "Condition.h"
#pragma once

class State;

class Transition
{
public:
	Transition(State* target, Condition* condition) : m_target(target), m_condition(condition) {}
	~Transition() {}

	State* getTargetState() { return m_target; }
	bool hasTriggered(Agent* agent)
	{
		return m_condition->test(agent);
	}

private:
	State* m_target;
	Condition* m_condition;
};