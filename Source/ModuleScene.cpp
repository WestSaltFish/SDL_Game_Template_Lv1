#include "ModuleScene.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{
   
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Init()
{
    return true;

    for (int i = 0; i < NUM_SCENES; i++)
    {
        if(scenes[i]) scenes[i]->Init();
    }
}

bool ModuleScene::Start()
{
    if(scenes[currentSceneIndex])   scenes[currentSceneIndex]->Start();

    return true;
}

UpdateResult ModuleScene::PreUpdate()
{
    if (scenes[currentSceneIndex])   scenes[currentSceneIndex]->PreUpdate();

    return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleScene::Update()
{
    if (scenes[currentSceneIndex])   scenes[currentSceneIndex]->Update();

    return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleScene::PostUpdate()
{
    if (scenes[currentSceneIndex])   scenes[currentSceneIndex]->PostUpdate();

    return UpdateResult::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
    for (int i = 0; i < NUM_SCENES; i++)
    {
        if (scenes[i]) scenes[i]->CleanUp();
    }

    return true;
}

void ModuleScene::ChangeScene(SceneName targetScene)
{
    scenes[currentSceneIndex]->CleanUp();
    currentSceneIndex = targetScene;
    scenes[currentSceneIndex]->Start();
}
