#include "WithinRangeCondition.h"

bool WithinRangeCondition::test(Agent* agent) const
{
	// Get the target position
	Vector2 targetPos = m_target->getPosition();

	// Get this agent's position
	Vector2 pos = agent->getPosition();

	// Find the distance
	float distance = (targetPos - pos).magnitude();

	// Return the result
	return distance <= m_range;
}