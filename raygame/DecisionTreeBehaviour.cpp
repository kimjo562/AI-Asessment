#include "DecisionTreeBehaviour.h"

void DecisionTreeBehaviour::update(Agent * agent, float deltaTime)
{
	m_rootDecision->makeDecision(agent, deltaTime);
}
