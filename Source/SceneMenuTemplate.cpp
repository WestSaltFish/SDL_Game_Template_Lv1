#include "SceneMenuTemplate.h"

SceneMenuTemplate::SceneMenuTemplate()
{
}

bool SceneMenuTemplate::Start()
{
	// Declare and initialize every GameObject on the scene before calling SceneGame::Start()

	SceneMenu::Start();
	return true;
}

void SceneMenuTemplate::PreUpdate()
{
	SceneMenu::PreUpdate();
}

void SceneMenuTemplate::Update()
{
	SceneMenu::Update();
}

void SceneMenuTemplate::PostUpdate()
{
	SceneMenu::PostUpdate();
}

void SceneMenuTemplate::CleanUp()
{
	SceneMenu::CleanUp();
}
