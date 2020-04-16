#include "StatBehaviour.h"

void StatBehaviour::update(Agent * agent, float deltaTime)
{
	float health = agent->getHealth();
	health = health - 0.001f;

	float hunger = agent->getHunger();
	hunger = hunger - 0.005f;

	float thirst = agent->getThirst();
	thirst = thirst - 0.01f;

	agent->addHealth(health);
	agent->addFood(hunger);
	agent->addWater(thirst);
}
