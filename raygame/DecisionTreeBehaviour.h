#include "Behaviour.h"
#include "Decision.h"
#pragma once

class DecisionTreeBehaviour : public Behaviour
{
public:
	DecisionTreeBehaviour(Decision* decision) : m_rootDecision(decision) {}
	virtual ~DecisionTreeBehaviour() {}

	virtual void update(Agent* agent, float deltaTime);

private:
	Decision* m_rootDecision;
};

