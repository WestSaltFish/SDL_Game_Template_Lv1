#include "Collider.h"
#include "Application.h"
#include "ModuleCollisions.h"

Collider::Collider(SDL_Rect rectangle, GameObject* gameObject, std::string tag, iPoint offset)
{
	this->rect = rectangle;
	this->gameObject = gameObject;
	this->tag = tag;
	this->offsetWithGameObject = offset;
	App->collisions->AddCollider(this);
}

void Collider::SetPos(int x, int y)
{
	rect.x = x + offsetWithGameObject.x;
	rect.y = y + offsetWithGameObject.y;
}

void Collider::SetPos(iPoint pos)
{
	rect.x = pos.x + offsetWithGameObject.x;
	rect.y = pos.y + offsetWithGameObject.y;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	// L6: DONE 1: Check if there is an overlap
	// between argument "r" and property "rect"
	return (rect.x < r.x + r.w &&
			rect.x + rect.w > r.x &&
			rect.y < r.y + r.h &&
			rect.h + rect.y > r.y);
}