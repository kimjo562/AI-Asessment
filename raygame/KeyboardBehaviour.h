#include "Behaviour.h"
#pragma once

class KeyboardBehaviour : public Behaviour
{
public:
	KeyboardBehaviour() {}
	virtual ~KeyboardBehaviour() {}
	virtual void update(Agent* agent, float deltaTime);
};