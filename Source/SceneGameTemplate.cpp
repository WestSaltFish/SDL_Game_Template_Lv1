#include "SceneGameTemplate.h"
#include "PlayerTemplate.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "TestPowerUp.h"

SceneGameTemplate::SceneGameTemplate()
{
}

bool SceneGameTemplate::Start()
{
	// Declare and initialize every GameObject on the scene before calling SceneGame::Start()

	new PlayerTemplate({ 5, 5});

	#pragma region Create PoweUp

	bool bad = true;

	for (int i = 0; i < 10; i++)
	{
		int x = (rand() % 200) + 10;
		int y = (rand() % 200) + 10;

		new TestPowerUp({ x,y }, bad);

		bad = false;
	}

	#pragma endregion

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
