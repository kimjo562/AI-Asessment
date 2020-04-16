#include "ScreenBehaviour.h"

void ScreenBehaviour::update(Agent * agent, float deltaTime)
{
	float x = agent->getPosition().x + agent->getVelocity().x;
	float y = agent->getPosition().y + agent->getVelocity().y;

	Vector2 force = { 0, 0 };

	//If out of bounds
	if (x < 50 || x >= 1580 || y < 60 || y >= 840) {
		//Get this agent's position
		Vector2 pos = agent->getPosition();
		//Target the center
		Vector2 targetPos = { 800, 450 };

		//Calculate the vector describing the direction to the target and normalize it
		Vector2 direction = targetPos - pos;
		direction = direction.normalize();
		//Multiply the direction by the speed we want the agent to move
		force = direction * agent->getSpeed();
		//Subtract the agent's current velocity from the result to get the force we need to apply
		force = force - agent->getVelocity();
	}

	agent->addForce(force * deltaTime);
}
