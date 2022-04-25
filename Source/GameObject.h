#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Point.h"
#include "RenderObject.hpp"

#define MAX_RENDEROBJECT 2

class Collider;

class GameObject
{
public:
	std::string name = "gameObject";

	bool pendingToDelete = false;

protected:
	Collider* col = nullptr;

	RenderObject renderObjects[MAX_RENDEROBJECT];

	iPoint position = { 0,0 };

public:
	GameObject(iPoint position = { 0,0 }, std::string name = "gameObject");

	virtual ~GameObject();

	virtual void Start();

	virtual void PreUpdate();

	virtual void Update();

	virtual void PostUpdate();

	virtual void OnCollisionEnter(GameObject* g);

	virtual void OnCollisionExit(GameObject* g);

	virtual void CleanUp();

protected:
	void AddtoList();
};

#endif // !__GAMEOBJECT_H__


