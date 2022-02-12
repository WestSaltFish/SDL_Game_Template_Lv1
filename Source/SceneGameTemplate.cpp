#include "SceneGameTemplate.h"

SceneGameTemplate::SceneGameTemplate()
{
}

bool SceneGameTemplate::Start()
{
	// Declare and initialize every GameObject on the scene before calling SceneGame::Start()

	SceneGame::Start();
	return true;
}

void SceneGameTemplate::PreUpdate()
{
	SceneGame::PreUpdate();
}

void SceneGameTemplate::Update()
{
	SceneGame::Update();
}

void SceneGameTemplate::PostUpdate()
{
	SceneGame::PostUpdate();
}

void SceneGameTemplate::CleanUp()
{
	SceneGame::CleanUp();
}
