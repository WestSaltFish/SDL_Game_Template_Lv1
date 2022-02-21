#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__
#include "Scene.h"
class SceneGame : public Scene
{
	// Add here any GameObject classes that every Game Scene requires
	// Example: Player class, Wall class, Enemies classes...

	// Player* player = nullptr;

public:

	SceneGame();

	bool Start() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void CleanUp() override;

};
#endif
