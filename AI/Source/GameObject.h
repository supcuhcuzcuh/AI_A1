#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "StateMachine.h"
struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_GOBLIN,
		GO_BALL,
		GO_CROSS,
		GO_CIRCLE,
		GO_CAMP1,
		GO_CAMP2,
		GO_CAMP3,
		GO_CAMP4,
		GO_FISH,
		GO_SHARK,
		GO_FISHFOOD,
		GO_TOTAL, //must be last
	};
	enum STATE
	{
		STATE_NONE = 0,
		STATE_TOOFULL,
		STATE_FULL,
		STATE_HUNGRY,
		STATE_DEAD,
	};
	float energy;
	float moveSpeed;
	float countDown;
	float mass;

	Vector3 pos;
	Vector3 vel;
	Vector3 scale;


	STATE currentState;
	GAMEOBJECT_TYPE type;

	int id;
	int steps;
	Vector3 target;

	bool active;
	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool moveDown;

	StateMachine* machine; // every gameobject will have a state machine
	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();
};

#endif