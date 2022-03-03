#include "SceneGameTemplate.h"
#include "PlayerTemplate.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "TestPowerUp.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleAudio.h"

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
	// To create a class inherited to the GameObject, you only need to make new,
	// It will take care of managing Start, Updates and even delete.
	// If you want to have a reference to this GameObject, you can store it in a pointer
	player = new PlayerTemplate({ 5, 5});

	// If you not, you can create it directly and forget about it.
	#pragma region Create PowerUps

	// The first PowerUp will be bad, and it will kill the player on a collision
	bool bad = true;

	for (int i = 0; i < powerUps ; i++)
	{
		int x = (rand() % 200) + 10;
		int y = (rand() % 200) + 10;

		new TestPowerUp({ x,y }, &powerUps, bad);

		bad = false;
	}

	#pragma endregion

	#pragma region Init win lose textures and audio

	winTex = App->textures->Load("Assets/Images/win.png");

	loseTex = App->textures->Load("Assets/Images/lose.png");

	winSFX = App->audio->LoadFx("Assets/Audio/win.wav");

	loseSFX = App->audio->LoadFx("Assets/Audio/lose.wav");

	#pragma endregion

	SceneGame::Start();

	return true;
}

void SceneGameTemplate::PreUpdate()
{
	if (player && player->pendingToDelete && gameState != 2)
	{
		player = nullptr;
		gameState = 2;
		App->audio->PlayFx(loseSFX);
	}

	if (powerUps <= 1 && gameState != 1)
	{
		gameState = 1;
		App->audio->PlayFx(winSFX);
	}

	SceneGame::PreUpdate();
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
		App->render->AddTextureRenderQueue(winTex, { 0,0 }, { 0,0,0,0 }, 1, -1);

		player->moveBlock = true;
	}
	else if (gameState == 2)
	{
		App->render->AddTextureRenderQueue(loseTex, { 0,0 }, { 0,0,0,0 }, 1, App->render->topLayer);
	}

	SceneGame::PostUpdate();
}

void SceneGameTemplate::CleanUp()
{
	SceneGame::CleanUp();
}
