#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

bool Scene::Init()
{
    return true;
}

bool Scene::Start()
{
    for (int i = 0; i < gameObjects.count(); i++)
    {
        if (gameObjects[i] != nullptr)
        {
            gameObjects[i]->Start();
        }
    }

    return true;
}

void Scene::PreUpdate()
{
    for (int i = 0; i < gameObjects.count(); i++)
    {
        if (gameObjects[i] != nullptr)
        {
            gameObjects[i]->PreUpdate();
        }
    }
}

void Scene::Update()
{
    for (int i = 0; i < gameObjects.count(); i++)
    {
        if (gameObjects[i] != nullptr)
        {
            gameObjects[i]->Update();
        }
    }
}

void Scene::PostUpdate()
{
    for (int i = 0; i < gameObjects.count(); i++)
    {
        if (gameObjects[i] != nullptr)
        {
            gameObjects[i]->PostUpdate();
        }
    }
}

void Scene::CleanUp()
{
    for (int i = 0; i < gameObjects.count(); i++)
    {
        if (gameObjects[i] != nullptr)
        {
            gameObjects[i]->CleanUp();
        }
    }
    
    gameObjects.clearPtr();
}
