#include "SceneGameTemplate.h"
#include "PlayerTemplate.h"
#include "Application.h"
#include "ModuleTextures.h"

SceneGameTemplate::SceneGameTemplate()
{
}

bool SceneGameTemplate::Start()
{
	// Declare and initialize every GameObject on the scene before calling SceneGame::Start()

	new PlayerTemplate({ 20,20 });

	//App->textures->Load("Assets/Images/DinoSprites-vita24x24.png");
	//App->textures->Load("Assets/Images/DinoSprites-vita24x24.png");
	//App->textures->Load("Assets/Images/DinoSprites-vita24x24.png");
	//App->textures->Load("Assets/Images/DinoSprites-vita24x24.png");

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
