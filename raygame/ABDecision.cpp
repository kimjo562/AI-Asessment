#include "ABDecision.h"

void ABDecision::makeDecision(Agent * agent, float deltaTime)
{
	if (m_condition->test(agent))
		m_a->makeDecision(agent, deltaTime);
	else
		m_b->makeDecision(agent, deltaTime);
}
