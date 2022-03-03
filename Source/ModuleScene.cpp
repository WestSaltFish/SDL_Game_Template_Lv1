#include "ModuleScene.h"
#include "SceneMenuTemplate.h"
#include "SceneGameTemplate.h"
#include "Application.h"
#include "ModuleRender.h"

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

    if (isChangingScene)   ChangeSceneSteptoStep();

    return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleScene::PostUpdate()
{
    if (scenes[currentSceneIndex])   scenes[currentSceneIndex]->PostUpdate();

    if (isChangingScene)
    {
        if (fade != 0) App->render->AddRectRenderQueue(SDL_Rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, 0, 0, 0, fade, App->render->topLayer, 200);
       
        StartChangeScene();
    } 

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

bool ModuleScene::StartChangeScene()
{
    if (changeTo >= 0 && changeSceneRequest)
    {
        changeSceneRequest = false;

        if (scenes[changeTo] == nullptr) return false;

        scenes[currentSceneIndex]->CleanUp();   

        currentSceneIndex = (SceneName)changeTo;

        scenes[currentSceneIndex]->Start();

        fadeSpeed = -fadeSpeed;

        changeTo = -1;

        changeState = SCENECHANGESTATES::fade_out;
    }

    return true;
}

void ModuleScene::ChangeSceneSteptoStep()
{
    fade += fadeSpeed;

    if(fade>=253)
    {
        printf("hi");
    }

    fade = fade > 255 ? 255 : fade < 0 ? 0 : fade;

    switch (changeState)
    {
    case SCENECHANGESTATES::idle:

        break;
    case SCENECHANGESTATES::fade_in:
        if (fade >= 255)
        {
            changeSceneRequest = true;
            changeState = SCENECHANGESTATES::idle;
        }
        break;
    case SCENECHANGESTATES::fade_out:
        if (fade <= 0)
        {
            changeState = SCENECHANGESTATES::idle;
            isChangingScene = false;
        }
        break;
    }
}

void ModuleScene::ChangeCurrentSceneRequest(uint index, float changeSpeed)
{
    if(!isChangingScene)
    {
        changeTo = index;

        if (scenes[changeTo] == nullptr) return;

        isChangingScene = true;

        changeState = SCENECHANGESTATES::fade_in;

        fadeSpeed = changeSpeed;
    }   
}