#include "SceneGameTemplate.h"
#include "PlayerTemplate.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "TestPowerUp.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleScene.h"

SceneGameTemplate::SceneGameTemplate()
{
}

bool SceneGameTemplate::Start()
{
	// IMPORTANT: Init the parameters of this scene
	// because when we restart the scene, these values should be set by default
	gameState = 0;

	powerUps = 10;

	// Declare and initialize every GameObject on the scene before calling SceneGame::Start()

	player = new PlayerTemplate({ 5, 5});

	#pragma region Create PoweUp

	bool bad = true;

	for (int i = 0; i < powerUps ; i++)
	{
		int x = (rand() % 200) + 10;
		int y = (rand() % 200) + 10;

		new TestPowerUp({ x,y }, &powerUps, bad);

		bad = false;
	}

	#pragma endregion

	#pragma region Init win lose textures

	winTex = App->textures->Load("Assets/Images/win.png");

	loseTex = App->textures->Load("Assets/Images/lose.png");

	#pragma endregion

	SceneGame::Start();

	return true;
}

void SceneGameTemplate::PreUpdate()
{
	if (player && player->pendingToDelete)
	{
		player = nullptr;
		gameState = 2;
	}

	SceneGame::PreUpdate();

	if (powerUps <= 1)
	{
		gameState = 1;
	}
}

void SceneGameTemplate::Update()
{
	SceneGame::Update();

	// If we're win or lose
	if (gameState > 0)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN) App->scene->ChangeCurrentSceneRequest(0);
	}
}

void SceneGameTemplate::PostUpdate()
{
	// 0 = inGame, 1 = win, 2 = lose
	if (gameState == 1)
	{
		App->render->AddTextureRenderQueue(winTex, { 0,0 }, { 0,0,0,0 }, 1, App->render->uiLayer);

		player->moveBlock = true;
	}
	else if (gameState == 2)
	{
		App->render->AddTextureRenderQueue(loseTex, { 0,0 }, { 0,0,0,0 }, 1, App->render->uiLayer);
	}

	SceneGame::PostUpdate();
}

void SceneGameTemplate::CleanUp()
{
	SceneGame::CleanUp();
}
