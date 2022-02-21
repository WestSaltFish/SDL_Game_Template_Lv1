#include "MenuText.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleScene.h"

MenuText::MenuText()
{
	optionsTexture = App->textures->Load("Assets/Images/menuOptions.png");
}

void MenuText::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->scene->ChangeCurrentSceneRequest(SceneName::SCENE_GAME);
	}
}

void MenuText::PostUpdate()
{
	App->render->AddTextureRenderQueue(optionsTexture, { 10,0 }, { 0,0,0,0 }, 0.03f, 1);
}