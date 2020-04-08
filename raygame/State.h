#include"Agent.h"
#include <vector>
#pragma once

class Transition;

class State
{
public:
	State() {};
	virtual ~State() {}
	virtual void init(Agent* agent) {};
	virtual void update(Agent* agent, float deltaTime) = 0;
	virtual void exit(Agent* agent) {};

	void addTransition(Transition* transition) { m_transitions.push_back(transition); }
	Transition* getTriggeredTransition(Agent* agent);

protected:
	std::vector<Transition*> m_transitions;

};
