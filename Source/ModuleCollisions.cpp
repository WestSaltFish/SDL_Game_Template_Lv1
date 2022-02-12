#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "GameObject.h"
#include "Collider.h"

#include "External/SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

UpdateResult ModuleCollisions::PreUpdate()
{
	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// Skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// Avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// Skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			// If is coll
			if(c1->Intersects(c2->rect))
			{
				c1->gameObject->OnCollisionEnter(c2->gameObject);
				c2->gameObject->OnCollisionEnter(c1->gameObject);
			}
		}

		int count = 0;

		// Check if has collision exit in c1
		for (std::vector<Collider>::iterator it = c1->colliders.begin(); it!= c1->colliders.end(); ++it, ++count)
		{
			// If not coll
			if(!c1->Intersects(c1->colliders[count].rect))
			{
				// Collision exit
				c1->gameObject->OnCollisionExit(c1->colliders[count].gameObject);
				c1->colliders.erase(it);
				break;
			}
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) debug = !debug;

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleCollisions::PostUpdate()
{
	if (debug) DebugDraw();

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	//Uint8 alpha = 80;
	//for(uint i = 0; i < MAX_COLLIDERS; ++i)
	//{
	//	if(colliders[i] == nullptr)
	//		continue;
	//	
	//	switch(colliders[i]->type)
	//	{
	//		case Collider::Type::NONE: // white
	//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 255, alpha });
	//		break;
	//		case Collider::Type::WALL: // blue
	//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 0, 0, 255, alpha });
	//		break;
	//		case Collider::Type::PLAYER: // green
	//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 0, 255, 0, alpha });
	//		break;
	//		case Collider::Type::ENEMY: // red
	//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 0, 0, alpha });
	//		break;
	//		case Collider::Type::PLAYER_SHOT: // yellow
	//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 0, alpha });
	//		break;
	//		case Collider::Type::ENEMY_SHOT: // magenta
	//		App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 0, 255, 255, alpha });
	//		break;
	//	}
	//}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}