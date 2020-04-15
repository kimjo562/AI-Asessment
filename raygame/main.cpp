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
#include "KeyboardBehaviour.h"
#include "ScreenBehaviour.h"
#include "WanderBehaviour.h"
#include "SeekBehaviour.h"
#include "PursueBehaviour.h"
#include "EvadeBehaviour.h"
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
	player->setPosition(Vector2{ 200.0f, 200.0f });
	player->setSpeed(100.0f);
	player->setColor(WHITE);

	// Create the enemy
	Agent* enemy = new Agent();
	enemy->setPosition(Vector2{ 700.0f, 700.0f });
	enemy->setSpeed(200.0f);
	enemy->setColor(LIME);

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
	player->addBehaviour(screenBehaviour);
	enemy->addBehaviour(screenBehaviour);

	// Create the player's FSM
	FSM* playerFSM = new FSM();
	player->addBehaviour(playerFSM);

	// Create the enemy's FSM
	FSM* enemyFSM = new FSM();
	enemy->addBehaviour(enemyFSM);

	IdleState* idleState = new IdleState();
	playerFSM->addState(idleState);
	enemyFSM->addState(idleState);

	// Create and add the Evade state
	PreyEvadeState* evadeState = new PreyEvadeState(enemy, 125.0f);	
	playerFSM->addState(evadeState);
	//// Create and add the Hunger state
	//HungerState* hungerState = new HungerState(foodSource, 50.0f);		
	//playerFSM->addState(hungerState);
	//// Create and add the Thirst state
	//ThirstState* thirstState = new ThirstState(waterSource, 50.0f);	
	//playerFSM->addState(thirstState);

	// Create and add the attack state
	PredAtkState* attackState = new PredAtkState(player, 100.0f);		// (Target, Speed)
	enemyFSM->addState(attackState);

	// Create and add the condition for enemy
	Condition* withinEnemyRangeCond = new WithinRangeCondition(player, 100);		// (Target, Range Detection)
	enemyFSM->addCondition(withinEnemyRangeCond);
	// Create and add the Transition for enemy
	Transition* toAttackTransition = new Transition(attackState, withinEnemyRangeCond);
	enemyFSM->addTransition(toAttackTransition);
	idleState->addTransition(toAttackTransition);

	// Create and add the condition for player
	Condition* withinPlayerRangeCond = new WithinRangeCondition(enemy, 50);		// (Target, Range Detection)
	playerFSM->addCondition(withinPlayerRangeCond);
	// Create and add the Transition for player
	Transition* toEvadeTransition = new Transition(evadeState, withinPlayerRangeCond);
	playerFSM->addTransition(toEvadeTransition);
	idleState->addTransition(toEvadeTransition);

	// Set current state to idle
	playerFSM->setCurrentState(idleState);
	enemyFSM->setCurrentState(idleState);

	//Player Leaves
	EvadeBehaviour* evadeBehaviour = new EvadeBehaviour();
	evadeBehaviour->setTarget(enemy);
	BehaviourDecision* evadeDecision = new BehaviourDecision(evadeBehaviour);

	// Enemy Leaves
	WanderBehaviour* wanderBehaviour = new WanderBehaviour();
	BehaviourDecision* wanderDecision = new BehaviourDecision(wanderBehaviour);
	SeekBehaviour* seekBehaviour = new SeekBehaviour();
	seekBehaviour->setTarget(player);
	BehaviourDecision* seekDecision = new BehaviourDecision(seekBehaviour);
	PursueBehaviour* pursueBehaviour = new PursueBehaviour();
	pursueBehaviour->setTarget(player);
	BehaviourDecision* pursueDecision = new BehaviourDecision(pursueBehaviour);

	//Enemy Branches
	WithinRangeCondition* canSeePlayer = new WithinRangeCondition(player, 100);
	ABDecision* canSeePlayerDecision = new ABDecision(pursueDecision, seekDecision, canSeePlayer);
	WithinRangeCondition* canHearPlayer = new WithinRangeCondition(player, 250);
	ABDecision* canHearPlayerDecision = new ABDecision(canSeePlayerDecision, wanderDecision, canHearPlayer);

	// Player Branches
	WithinRangeCondition* canSeeEnemy = new WithinRangeCondition(enemy, 50);
	ABDecision* canSeeEnemyDecision = new ABDecision(pursueDecision, seekDecision, canSeeEnemy);
	WithinRangeCondition* canHearEnemy = new WithinRangeCondition(enemy, 125);
	ABDecision* canHearEnemyDecision = new ABDecision(canSeeEnemyDecision, wanderDecision, canHearEnemy);
	
	// Player Decision Tree
	DecisionTreeBehaviour* playerDecisionTree = new DecisionTreeBehaviour(canHearEnemyDecision);
	player->addBehaviour(playerDecisionTree);
	player->addBehaviour(screenBehaviour);

	// Enemy Decision Tree
	DecisionTreeBehaviour* enemyDecisionTree = new DecisionTreeBehaviour(canHearPlayerDecision);
	enemy->addBehaviour(enemyDecisionTree);
	enemy->addBehaviour(screenBehaviour);


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

		DrawText("Rabbit", player->getPosition().x - 6, player->getPosition().y - 10, 11, WHITE);

		static char buffer[10];
		sprintf_s(buffer, "%.0f", enemy->getSpeed());
		 DrawText(buffer, enemy->getPosition().x, enemy->getPosition().y - 10, 11, WHITE);

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