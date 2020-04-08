#include "Behaviour.h"
#pragma once

class ScreenBehaviour : public Behaviour
{
public:
	ScreenBehaviour() {}
	virtual ~ScreenBehaviour() {}

	virtual void update(Agent* agent, float deltaTime);
};

