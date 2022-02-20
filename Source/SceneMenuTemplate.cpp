#include "SceneMenuTemplate.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "MenuText.h"

SceneMenuTemplate::SceneMenuTemplate()
{
}

bool SceneMenuTemplate::Start()
{
	// Declare and initialize every GameObject on the scene before calling SceneGame::Start()

	SceneMenu::Start();

	// Not a GameObject, it's position is fixed and it does not require a Collider
	text = new MenuText();

	// Temporary texture for the menu background
	backgroundTex = App->textures->Load("Assets/Images/menuBackground.jpg");
	return true;
}

void SceneMenuTemplate::PreUpdate()
{
	SceneMenu::PreUpdate();
}

void SceneMenuTemplate::Update()
{
	text->Update();
	SceneMenu::Update();
}

void SceneMenuTemplate::PostUpdate()
{
	// Print background Texture

	App->render->AddTextureRenderQueue(backgroundTex, { 0,0 }, { 0,0,0,0 }, 0.5f);

	// Print text

	text->PostUpdate();

	SceneMenu::PostUpdate();
}

void SceneMenuTemplate::CleanUp()
{
	delete text;
	text = nullptr;
	SceneMenu::CleanUp();
}
