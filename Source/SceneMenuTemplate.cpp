#include "SceneMenuTemplate.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
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

	uint test1 = App->audio->LoadFx("Assets/Audio/test.mp3");
	uint test2 = App->audio->LoadFx("Assets/Audio/test.mp3");
	uint test3 = App->audio->LoadFx("Assets/Audio/test.mp3");
	uint test4 = App->audio->LoadFx("Assets/Audio/test.mp3");

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
	RELEASE(text);
	SceneMenu::CleanUp();
}
