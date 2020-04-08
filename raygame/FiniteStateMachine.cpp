#include "FiniteStateMachine.h"

FSM::~FSM()
{
	for (State* s : m_states)
		delete s;
	for (Transition* t : m_transitions)
		delete t;
	for (Condition* c : m_conditions)
		delete c;
}

void FSM::update(Agent* agent, float deltaTime)
{
	//Stop if we have no current state
	if (m_currentState == nullptr)
	{
		return;
	}
	//Check if a transition has been triggered
	Transition* transition = m_currentState->getTriggeredTransition(agent);
	//If there is a transition, change states
	if (transition != nullptr) {
		m_currentState->exit(agent);
		m_currentState = transition->getTargetState();
		m_currentState->init(agent);
	}
	//Update the current state
	m_currentState->update(agent, deltaTime);
}
