#include "SceneGame.h"
#include "Application.h"

SceneGame::SceneGame()
{

}

bool SceneGame::Start()
{
    Scene::Start();
    return true;
}

void SceneGame::PreUpdate()
{
    Scene::PreUpdate();
}

void SceneGame::Update()
{
    Scene::Update();
}

void SceneGame::PostUpdate()
{
    Scene::PostUpdate();
}

void SceneGame::CleanUp()
{
    Scene::CleanUp();
}
