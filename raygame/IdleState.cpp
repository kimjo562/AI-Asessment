#include "IdleState.h"

void IdleState::update(Agent * agent, float deltaTime)
{
	auto randVec = []() {
		float randX = (float)rand() - ((float)RAND_MAX) / 2;
		float randY = (float)rand() - ((float)RAND_MAX) / 2;
		return Vector2{ randX, randY };
	};

	//Start with a random target on the edge of a circle with a set radius around the agent
	Vector2 targetPos = randVec().normalize() * m_radius;
	//Add a randomized vector to the target, with a magnitude specified by a jitter amount
	targetPos += randVec().normalize() * m_jitter;
	//Bring the target back to the radius of the sphere by normalizing it and scaling by the radius
	targetPos = targetPos.normalize() * m_radius;
	//Add the agent’s heading, multiplied by the distance, to the target
	Vector2 heading = agent->getVelocity().normalize();
	targetPos += heading * m_offset;

	//Add the previous target
	targetPos += m_prevTarget;

	//Store previous target
	m_prevTarget.x = targetPos.x;
	m_prevTarget.y = targetPos.y;

	//Seek the target
	Vector2 pos = agent->getPosition();

	//Calculate the vector describing the direction to the target and normalize it 
	Vector2 direction = targetPos - pos;
	direction = direction.normalize();
	//Multiply the direction by the speed we want the agent to move
	direction = direction * 100;
	//Subtract the agent’s current velocity from the result to get the force we need to apply
	Vector2 force = direction - agent->getVelocity();

	//Apply the force
	agent->addForce(force * deltaTime);
}
