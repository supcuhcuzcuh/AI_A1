
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	moveSpeed(15.0f),
	active(false),
	mass(1.f),
	machine(nullptr)
{
	moveLeft = moveRight = moveUp = moveDown = true; 
}

GameObject::~GameObject()
{
}