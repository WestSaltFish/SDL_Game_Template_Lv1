#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Point.h"
#include <string>

class Collider;
class RenderObject;

class GameObject
{
public:
	std::string name = "gameObject";

private:
	Collider* col = nullptr;

	RenderObject* renderObject = nullptr;

	iPoint position = { 0,0 };

	bool pendingToDelete = false;

public:
	GameObject(iPoint position = { 0,0 }, std::string name = "gameObject");

	~GameObject();

	virtual void Start();

	virtual void PreUpdate();

	virtual void Update();

	virtual void PostUpdate();

	virtual void OnCollisionEnter(GameObject* g);

	virtual void OnCollisionExit(GameObject* g);

	virtual void CleanUp();
};

#endif // !__GAMEOBJECT_H__

