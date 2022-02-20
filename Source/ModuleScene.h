#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"
#include "Scene.h"

enum SceneName
{
	SCENE_MENU = 0,
	SCENE_GAME,
	NUM_SCENES
};

class ModuleScene : public Module
{
public:
	Scene* scenes[NUM_SCENES] = { nullptr };
	SceneName currentSceneIndex = SCENE_MENU;
public:
	// Constructor
	ModuleScene();

	// Destructor
	~ModuleScene();

	// Called after Init.
	bool Start() override;

	// Called at the beginning of the application loop
	UpdateResult PreUpdate() override;

	// Called at the middle of the application loop
	UpdateResult Update() override;

	// Called at the end of the application loop.
	UpdateResult PostUpdate() override;

	// Called on application exit.
	bool CleanUp() override;

	void ChangeScene(SceneName targetScene);
};

#endif // !__MODULESCENE_H__
