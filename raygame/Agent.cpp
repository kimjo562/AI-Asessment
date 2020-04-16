#include "Behaviour.h"
#include "Agent.h"

void Agent::update(float deltaTime)
{
	//Set total force to zero
	//For each Behavior in the Behavior list
	for (auto i = m_behaviourList.begin(); i != m_behaviourList.end(); i++)
	{
		//Call the Behavior's update function
		(*i)->update(this, deltaTime);
	}
	//Add velocity times delta time to position
	m_position += m_velocity * deltaTime;
}

void Agent::draw()
{
	DrawRectangle(m_position.x, m_position.y, 10, 10, m_color);
}

void Agent::addBehaviour(Behaviour* behaviour)
{
	// Add Behaviour to the Behaviour List
	m_behaviourList.insert(m_behaviourList.end(), behaviour);
}

void Agent::addForce(Vector2 force)
{
	m_velocity += force;
}

void Agent::addHealth(float health)
{
	m_health = health;
}

void Agent::addFood(float food)
{
	m_hunger = food;
}

void Agent::addWater(float water)
{
	m_thirst = water;
}