#include "raylib.h"
#include <vector>
#pragma once

class Behaviour;

class Agent
{
public:
	Agent() {}
	virtual ~Agent() {}

	//Update the agent and its behaviours
	virtual void update(float deltaTime);

	//Draw the agent
	virtual void draw();

	//Add a behavior to the agent
	void addBehaviour(Behaviour* behaviour);

	//Add a force to the agent's velocity
	void addForce(Vector2 force);

	void addHealth(float health);
	void addFood(float food);
	void addWater(float water);

	//Movement functions
	void setPosition(Vector2 position) { m_position = position; }
	Vector2 getPosition() { return m_position; }
	void setVelocity(Vector2 velocity) { m_velocity = velocity; }
	Vector2 getVelocity() { return m_velocity; }

	//Speed functions
	void setSpeed(float speed) { m_speed = speed; }
	float getSpeed() { return m_speed; }

	//Color functions
	void setColor(Color color) { m_color = color; }
	Color getColor() { return m_color; }

	float getHealth() { return m_health; }

	float setHunger(float hunger) { return m_hunger = hunger; }
	float getHunger() { return m_hunger; }

	float setThirst(float thirst) { return m_thirst = thirst; }
	float getThirst() { return m_thirst; }

protected:
	std::vector<Behaviour*> m_behaviourList;

	Vector2 m_position = { 0.0f, 0.0f };
	Vector2 m_velocity = { 0.0f, 0.0f };

	float m_speed = 200.0f;
	Color m_color = VIOLET;

	float m_health = 100.0f;
	float m_hunger = 100.0f;
	float m_thirst = 100.0f;
};