#ifndef __SCENE_MENU_TEMPLATE_H__
#define __SCENE_MENU_TEMPLATE_H__

#include "SceneMenu.h"

struct SDL_Texture;
class MenuText;

// Test class, should be removed at the start of the project
class SceneMenuTemplate : public SceneMenu
{
public:
	SceneMenuTemplate();

	bool Start() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void CleanUp() override;
private:
	SDL_Texture* backgroundTex = nullptr;
	MenuText* text = nullptr;
};

#endif