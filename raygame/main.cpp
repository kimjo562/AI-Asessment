/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "Agent.h"
#include "ScreenBehaviour.h"
#include "FiniteStateMachine.h"
#include "IdleState.h"
#include "PredAtkState.h"
#include "preyEvadeState.h"
#include "hungerState.h"
#include "thirstState.h"
#include "WithinRangeCondition.h"
#include "DecisionTreeBehaviour.h"
#include "ABDecision.h"
#include "BehaviourDecision.h"
#include "StatBehaviour.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1600;
	int screenHeight = 900;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	// Create the player
	Agent* player = new Agent();
	player->setPosition(Vector2{ 630.0f, 650.0f });
	player->setSpeed(120.0f);
	player->setColor(WHITE);

	// Create the enemy
	Agent* enemy = new Agent();
	enemy->setPosition(Vector2{ 700.0f, 700.0f });
	enemy->setSpeed(100.0f);
	enemy->setColor(RED);

	// Create the food point
	Agent* foodSource = new Agent();
	foodSource->setPosition(Vector2{ 1400.0f, 100.0f });
	foodSource->setSpeed(0.0f);
	foodSource->setColor(DARKGREEN);

	// Create the water point
	Agent* waterSource = new Agent();
	waterSource->setPosition(Vector2{ 500.0f, 700.0f });
	waterSource->setSpeed(0.0f);
	waterSource->setColor(SKYBLUE);

	//Create and add screen edge behavior
	ScreenBehaviour* screenBehaviour = new ScreenBehaviour();
	StatBehaviour* statBehaviour = new StatBehaviour();
	player->addBehaviour(statBehaviour);
	player->addBehaviour(screenBehaviour);
	enemy->addBehaviour(screenBehaviour);

	// Create the player's FSM
	FSM* playerFSM = new FSM();
	player->addBehaviour(playerFSM);

	// Create the enemy's FSM
	FSM* enemyFSM = new FSM();
	enemy->addBehaviour(enemyFSM);

	IdleState* preyIdleState = new IdleState();
	playerFSM->addState(preyIdleState);
	IdleState* predIdleState = new IdleState();
	enemyFSM->addState(predIdleState);

	// Create and add the Evade state
	PreyEvadeState* evadeState = new PreyEvadeState(enemy, 150.0f);	
	playerFSM->addState(evadeState);
	// Create and add the Hunger state
	HungerState* hungerState = new HungerState(foodSource, 75.0f);		
	playerFSM->addState(hungerState);
	// Create and add the Thirst state
	ThirstState* thirstState = new ThirstState(waterSource, 75.0f);	
	playerFSM->addState(thirstState);

	// Create and add the attack state
	PredAtkState* attackState = new PredAtkState(player, 100.0f);		// (Target, Speed)
	enemyFSM->addState(attackState);

	// Create and add the condition for enemy
	Condition* withinEnemyRangeCond = new WithinRangeCondition(player, 100);		// (Target, Range Detection)
	enemyFSM->addCondition(withinEnemyRangeCond);
	// Create and add the Transition for enemy
	Transition* toAttackTransition = new Transition(attackState, withinEnemyRangeCond);
	enemyFSM->addTransition(toAttackTransition);
	predIdleState->addTransition(toAttackTransition);

	// Create and add the condition for player
	Condition* withinPlayerRangeCond = new WithinRangeCondition(enemy, 110);		// (Target, Range Detection)
	playerFSM->addCondition(withinPlayerRangeCond);
	// Create and add the Transition for player
	Transition* toEvadeTransition = new Transition(evadeState, withinPlayerRangeCond);
	playerFSM->addTransition(toEvadeTransition);
	preyIdleState->addTransition(toEvadeTransition);

	// Set current state to idle
	playerFSM->setCurrentState(preyIdleState);
	enemyFSM->setCurrentState(predIdleState);


	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		float deltaTime = GetFrameTime();

		player->update(deltaTime);
		enemy->update(deltaTime);
		foodSource->update(deltaTime);
		waterSource->update(deltaTime);

		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(BLACK);

		static char buffer[10];

		DrawText("Rabbit", player->getPosition().x - 8, player->getPosition().y - 11, 11, WHITE);
		DrawText("Wolf", enemy->getPosition().x - 6, enemy->getPosition().y - 11, 11, WHITE);

		sprintf_s(buffer, "%.0f", player->getHealth());
		DrawText(buffer, 1500, 100, 14, RED);
		DrawText("Health: ", 1450, 100, 14, RED);
		sprintf_s(buffer, "%.0f", player->getHunger());
		DrawText(buffer, 1505, 120, 14, BROWN);
		DrawText("Hunger: ", 1450, 120, 14, BROWN);
		sprintf_s(buffer, "%.0f", player->getThirst());
		DrawText(buffer, 1500, 140, 14, SKYBLUE);
		DrawText("Thirst: ", 1450, 140, 14, SKYBLUE);

		player->draw();
		enemy->draw();
		foodSource->draw();
		waterSource->draw();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}