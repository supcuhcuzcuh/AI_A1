#include "SceneAssignment1.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneAssignment1::SceneAssignment1()
{
	for (int i = 0; i < 4; ++i)
	{
		camp[i] = nullptr;
	}
}

SceneAssignment1::~SceneAssignment1()
{
	for (int i = 0; i < 4; ++i)
	{
		delete camp[i];
	}
}

void SceneAssignment1::Init()
{
	SceneBase::Init();

	Math::InitRNG();
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// physics
	goSpeed = 1.0f;

	gridSize = m_worldHeight / noGrid;
	gridOffset = gridSize / 2;

	
	// init camp gameobjects
	camp[0] = InitGO(5.0f, 5.0f, GameObject::GO_CAMP1); 
	camp[1] = InitGO(5.0f, 95.0f, GameObject::GO_CAMP2);
	camp[2] = InitGO(95.0f, 95.0f, GameObject::GO_CAMP3);
	camp[3] = InitGO(95.0f, 5.0f, GameObject::GO_CAMP4);
} 

GameObject* SceneAssignment1::FetchGO(GameObject::GAMEOBJECT_TYPE type)
{
	for (auto go : goList)
	{
		if (!go->active && go->type == type)
		{
			go->active = true;
			goObjCount++;
			return go; // return one gameobject
		}
	}
	for (unsigned int i = 0; i < 10; ++i)
	{
		// GameObject* newGob = new GameObject(GameObject::GO_GOBLIN); memleak
		GameObject* newGob = InitGO(20, 20, GameObject::GO_GOBLIN);
		goList.push_back(newGob);
	}
	return FetchGO(type);
}

//Exercise: This function should return 0 to 8, i.e. AI player's decision to put circle on one of the grids
int SceneAssignment1::GetAIDecision()
{
	return 0;
}

void SceneAssignment1::ProcessInput()
{
	static bool bSpaceState = false;
	if (!bSpaceState && Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = true;
		GameObject* newGob = FetchGO(GameObject::GO_GOBLIN);
		//GameObject* newGob = InitGO(20, 20, GameObject::GO_GOBLIN);
		std::cout << "GO POS: " << newGob->pos << "GO SCALE: " << newGob->scale << std::endl;
	}
	else if (bSpaceState && !Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = false;
	}
	if (Application::IsKeyPressed(0x46)) // if user press F
	{
		std::cout << bSpaceState << std::endl; 
	}
}

GameObject* SceneAssignment1::InitGO(float posX, float posY, GameObject::GAMEOBJECT_TYPE type)
{
	GameObject* go = new GameObject(type);
	switch (type)
	{
	case GameObject::GO_GOBLIN:
		go->pos.Set(posX, posY, 0);
		go->scale.Set(7,7,7);
		go->machine = new StateMachine();
		go->machine->AddState(new GoblinTravel("GoblinTravel"));
		go->machine->AddState(new GoblinRangeAttack("GoblinRange"));
		go->machine->AddState(new GoblinEatingState("GoblinEating"));
		go->machine->AddState(new GoblinRestingState("GoblinRest"));
		break;
	default:
		go->pos.Set(posX, posY, 0);
		go->scale.Set(7, 7, 7);
		break;
	}
	return go;
}

void SceneAssignment1::Update(double dt)
{	
	ProcessInput();
	SceneBase::Update(dt);

	//Movement Section
	for (std::vector<GameObject*>::iterator it = goList.begin(); it != goList.end(); ++it)
	{
		GameObject* go = (GameObject*)*it;
		if (!go->active)
			continue;
		std::cout << "yur" << std::endl;
		Vector3 dir = go->target - go->pos;
		if (dir.Length() < go->moveSpeed * dt)
		{
			//GO->pos reach target
			go->pos = go->target;
			float random = Math::RandFloatMinMax(0.f, 1.f);
			if (random < 0.25f && go->moveRight)
				go->target = go->pos + Vector3(gridSize, 0, 0);
			else if (random < 0.5f && go->moveLeft)
				go->target = go->pos + Vector3(-gridSize, 0, 0);
			else if (random < 0.75f && go->moveUp)
				go->target = go->pos + Vector3(0, gridSize, 0);
			else if (go->moveDown)
				go->target = go->pos + Vector3(0, -gridSize, 0);
			if (go->target.x < 0 || go->target.x > noGrid * gridSize || go->target.y < 0 || go->target.y > noGrid * gridSize)
				go->target = go->pos;
		}
		else
		{
			try
			{
				dir.Normalize();
				go->pos += dir * go->moveSpeed * static_cast<float>(dt);
			}
			catch (DivideByZero)
			{
			}
		}
	}
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
}


void SceneAssignment1::RenderGO(std::vector<GameObject*> goVector)
{
	for (auto& element : goVector)
	{
		switch (element->type)
		{
		case GameObject::GO_GOBLIN:
			modelStack.PushMatrix();
			modelStack.Translate(element->pos.x, element->pos.y, element->pos.z);
			modelStack.Scale(element->scale.x, element->scale.y, element->scale.z);
			RenderMesh(meshList[GEO_GOBLIN], FALSE);
			modelStack.PopMatrix();
			break;
		default:
			break;
		}
	}
}

void SceneAssignment1::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderMesh(meshList[GEO_AXES], false);

	//std::cout << camp->pos << std::endl;

	modelStack.PushMatrix();
	modelStack.Translate(m_worldHeight * 0.5f, m_worldHeight * 0.5f, -1.f);
	modelStack.Scale(m_worldHeight, m_worldHeight, m_worldHeight);
	RenderMesh(meshList[GEO_GRID], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camp[0]->pos.x, camp[0]->pos.y, camp[0]->pos.z);
	modelStack.Scale(camp[0]->scale.x, camp[0]->scale.y, camp[0]->scale.z);
	RenderMesh(meshList[GEO_CAMP1], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camp[1]->pos.x, camp[1]->pos.y, camp[1]->pos.z);
	modelStack.Scale(camp[1]->scale.x, camp[1]->scale.y, camp[1]->scale.z);
	RenderMesh(meshList[GEO_CAMP2], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camp[2]->pos.x, camp[2]->pos.y, camp[2]->pos.z);
	modelStack.Scale(camp[2]->scale.x, camp[2]->scale.y, camp[2]->scale.z);
	RenderMesh(meshList[GEO_CAMP3], false);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(camp[3]->pos.x, camp[3]->pos.y, camp[3]->pos.z);
	modelStack.Scale(camp[3]->scale.x, camp[3]->scale.y, camp[3]->scale.z);
	RenderMesh(meshList[GEO_CAMP4], false);
	modelStack.PopMatrix();

	RenderGO(goList);
}

void SceneAssignment1::Exit()
{
	SceneBase::Exit();
}
