#pragma once
#include "Scene.h"
class SceneMenu : public Scene
{
	// Add here any GameObject classes that every Menu Scene requires
	// Example: GUI class, Background class...

    // Background* bg = nullptr;
public:

	SceneMenu();

	bool Init() override;

	bool Start() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void CleanUp() override;

};

