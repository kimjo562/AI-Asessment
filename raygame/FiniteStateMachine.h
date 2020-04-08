#include "Transition.h"
#include "Condition.h"
#include "State.h"
#include "Behaviour.h"
#pragma once

class FSM : public Behaviour
{
public:
	FSM() : m_currentState(nullptr) {}
	virtual ~FSM();

	// add components, takes ownership
	void addState(State* state) { m_states.push_back(state); }
	void addTransition(Transition* transition) { m_transitions.push_back(transition); }
	void addCondition(Condition* condition) { m_conditions.push_back(condition); }

	void setCurrentState(State* state) { m_currentState = state; }
	State* getCurrentState() { return m_currentState; }

	virtual void update(Agent* agent, float deltaTime);

protected:
	std::vector<State*> m_states;
	std::vector<Transition*> m_transitions;
	std::vector<Condition*> m_conditions;

	State* m_currentState;
};