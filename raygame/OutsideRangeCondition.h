#include "Condition.h"
#pragma once

class OutsideRangeCondition : public Condition {
public:
	OutsideRangeCondition(Agent* target, float range) : m_target(target), m_range(range) {}
	virtual ~OutsideRangeCondition() {}

	virtual bool test(Agent* agent) const;

private:
	Agent* m_target;
	float m_range;
};