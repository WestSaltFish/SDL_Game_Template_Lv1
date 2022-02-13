#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "External/SDL/include/SDL_Rect.h"
#include "List.h"

class Module;
class GameObject;

struct Collider
{
	// Methods
	Collider(SDL_Rect rectangle);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	// Variables
	SDL_Rect rect;
	GameObject* gameObject = nullptr;

	List<Collider*> colliders;
};

#endif // !__COLLIDER_H__