#include "ModuleScene.h"
#include "SceneMenuTemplate.h"
#include "SceneGameTemplate.h"

ModuleScene::ModuleScene() : Module()
{
    scenes[SCENE_MENU] = new SceneMenuTemplate();
    scenes[SCENE_GAME] = new SceneGameTemplate();
}

ModuleScene::~ModuleScene()
{
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
        if (scenes[i])
        {
            scenes[i]->CleanUp();
            RELEASE(scenes[i]);
        }
    }

    return true;
}

void ModuleScene::ChangeScene(SceneName targetScene)
{
    scenes[currentSceneIndex]->CleanUp();
    currentSceneIndex = targetScene;
    scenes[currentSceneIndex]->Start();
}
