#ifndef __SCENE_GAME_TEMPLATE_H__
#define __SCENE_GAME_TEMPLATE_H__

#include "SceneGame.h"

class PlayerTemplate;


// Test class, should be removed at the start of the project
class SceneGameTemplate : public SceneGame
{
public:

	SceneGameTemplate();

	bool Start() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void CleanUp() override;

private:

	PlayerTemplate* player = nullptr;

	SDL_Texture* winTex = nullptr;

	SDL_Texture* loseTex = nullptr;

	int powerUps = 10;

	int gameState = 0; // 0 = inGame, 1 = win, 2 = lose

	uint winSFX, loseSFX;
};
#endif
