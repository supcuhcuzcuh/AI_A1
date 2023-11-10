#ifndef SCENE_ASSIGNMENT1_H
#define SCENE_ASSIGNMENT1_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include <map>
#include "GoblinStates.h"
using namespace std;

class SceneAssignment1 : public SceneBase
{
public:
	SceneAssignment1();
	~SceneAssignment1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(std::vector<GameObject*> goVector);

	GameObject* FetchGO(GameObject::GAMEOBJECT_TYPE type);

	int GetAIDecision();
protected:
	std::vector<GameObject*> goList;
	void ProcessInput();

	GameObject* InitGO(float posX, float posY, GameObject::GAMEOBJECT_TYPE);
	GameObject* InitGoblinStates();
	vector<vector<GameObject>> allEnemies;
	std::vector<GameObject*> goblin;
	GameObject* camp[4];
	GameObject* iterator;

	int goObjCount;
	int noGrid;

	float goSpeed;
	float m_worldWidth;
	float m_worldHeight;
	float gridSize;
	float gridOffset;
	float m_speed;
};

#endif