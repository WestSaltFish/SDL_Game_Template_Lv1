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

}

void MenuText::PostUpdate()
{
	App->render->AddTextureRenderQueue(optionsTexture, { 15,10 }, { 0,0,0,0 }, 1, 1);
}