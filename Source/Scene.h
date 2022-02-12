#ifndef __SCENE_H__
#define __SCENE_H__

#include "GameObject.h"
#include "List.h"

class Scene
{
public:
	Scene();

	~Scene();

	virtual bool Init();

	virtual bool Start();

	virtual void PreUpdate();

	virtual void Update();

	virtual void PostUpdate();

	virtual void CleanUp();

	List<GameObject*> gameObjects;
};

#endif // !__SCENE_H__