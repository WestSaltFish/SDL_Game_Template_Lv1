#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{
}

Scene::~Scene()
{
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
            if(gameObjects[i]->pendingToDelete)  DestroyedGameObject(gameObjects[i]);
            
            else gameObjects[i]->PreUpdate();
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

void Scene::AddGameObject(GameObject* g)
{
    gameObjects.add(g);
}

void Scene::DestroyedGameObject(GameObject* g)
{
    // Get index of this gameObject in global gameobjects list
    int index = gameObjects.find(g);

    // If exist in the list
    if (index >= 0)
    {
        // Delete and remove this gameobject in the list
        gameObjects.delPtr(gameObjects.At(index));
    }
}
