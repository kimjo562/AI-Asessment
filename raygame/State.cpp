#include "State.h"
#include "Transition.h"

Transition* State::getTriggeredTransition(Agent* agent)
{
	// Iterate through all the transitions in our list, checking to see if they have triggered
	for (Transition* transition : m_transitions) {
		if (transition->hasTriggered(agent))
			return transition;
	}
	return nullptr;
}
