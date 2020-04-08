#include "Condition.h"
#include "Decision.h"
#pragma once

class ABDecision : public Decision
{
public:
	ABDecision(Decision* a, Decision* b, Condition* condition)
		: m_a(a), m_b(b), m_condition(condition) {}
	~ABDecision() {}

	virtual void makeDecision(Agent* agent, float deltaTime);

private:
	Decision* m_a;
	Decision* m_b;
	Condition* m_condition;
};

