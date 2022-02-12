#pragma once
#include "SceneMenu.h"
class SceneMenuTemplate : public SceneMenu
{
	SceneMenuTemplate();

	bool Start() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void CleanUp() override;
};

