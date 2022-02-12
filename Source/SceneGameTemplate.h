#pragma once
#include "SceneGame.h"
class SceneGameTemplate : public SceneGame
{
public:

	SceneGameTemplate();

	bool Start() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void CleanUp() override;


};

