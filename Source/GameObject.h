#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Point.h"
#include <string>

class Collider;

class GameObject
{
public:
	std::string name = "gameObject";

	Collider* col = nullptr;

	iPoint position = { 0,0 };

public:
	GameObject();

	~GameObject();

	void Start();

	void PreUpdate();

	void Update();

	void PostUpdate();

	void Clean();
};

#endif // !__GAMEOBJECT_H__


