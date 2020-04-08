#include "Agent.h"
#pragma once

class Decision
{
public:
	virtual void makeDecision(Agent* agent, float deltatime) = 0;
};