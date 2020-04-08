#include "BehaviourDecision.h"
#include "Behaviour.h"

void BehaviourDecision::makeDecision(Agent * agent, float deltaTime)
{
	if (m_behaviour == nullptr)
		return;

	m_behaviour->update(agent, deltaTime);
}
