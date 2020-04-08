#include "Behaviour.h"
#pragma once

class Condition : public Behaviour
{
public:
	Condition() {}
	virtual ~Condition() {}

	virtual bool test(Agent* agent) const = 0;

	virtual void update(Agent* agent, float deltaTime) {}
};