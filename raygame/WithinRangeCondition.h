#include "Condition.h"
#pragma once

class WithinRangeCondition : public Condition {
public:
	WithinRangeCondition(Agent* target, float range)
		: m_target(target), m_range(range) {}
	virtual ~WithinRangeCondition() {}

	virtual bool test(Agent* agent) const;

private:
	Agent* m_target;
	float m_range;
};