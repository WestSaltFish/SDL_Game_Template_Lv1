#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include <string>
#include "External/SDL/include/SDL_Rect.h"
#include "List.h"
#include "Point.h"

class Module;
class GameObject;

struct Collider
{
public:
	// Methods
	Collider(SDL_Rect rectangle, GameObject* gameObject, std::string tag = "None", iPoint offset = { 0,0 });

	void SetPos(int x, int y);

	void SetPos(iPoint pos);

	bool Intersects(const SDL_Rect& r) const;

public:
	// Variables
	SDL_Rect rect;

	GameObject* gameObject = nullptr;

	std::string tag = "None";

private:
	iPoint offsetWithGameObject = { 0,0 };

	List<Collider*> colliders;

	friend class ModuleCollisions;
};

#endif // !__COLLIDER_H__