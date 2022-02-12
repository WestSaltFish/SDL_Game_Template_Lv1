#ifndef __SCENE_GAME_TEMPLATE_H__
#define __SCENE_GAME_TEMPLATE_H__
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
#endif
