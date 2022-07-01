#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include <string>
#include "SDL_Rect.h"
#include "List.h"
#include "Point.h"

class Module;
class GameObject;

struct Collider
{
public:
	// Methods

	/// <summary>
	/// Contructor
	/// </summary>
	/// <param name="rectangle"> collider size </param>
	/// <param name="gameObject"> gameObject whose will be call on collisions </param>
	/// <param name="tag"> a simple tag a this collider </param>
	/// <param name="offset"> offset between this collider and his gameObject </param>
	Collider(SDL_Rect rectangle, GameObject* gameObject, std::string tag = "None", iPoint offset = { 0,0 });

	void SetPos(int x, int y);

	void SetPos(iPoint pos);

	bool Intersects(const SDL_Rect& r) const;

public:
	// Variables
	SDL_Rect rect;

	GameObject* gameObject = nullptr;

	std::string tag = "None";

	SDL_Color debugColor = { 0, 0, 0, 150};

private:
	iPoint offsetWithGameObject = { 0,0 };

	List<Collider*> colliders;

	friend class ModuleCollisions;
};

#endif // !__COLLIDER_H__