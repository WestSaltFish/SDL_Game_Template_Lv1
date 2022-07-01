#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "GameObject.h"
#include "Collider.h"


ModuleCollisions::ModuleCollisions() : Module()
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i) colliders[i] = nullptr;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

UpdateResult ModuleCollisions::PreUpdate()
{
	Collider* c1 = nullptr;
	Collider* c2 = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// Skip empty colliders
		if(colliders[i] == nullptr) continue;

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
				// Add in collider list
				c1->colliders.add(c2);

				c2->gameObject->OnCollisionEnter(c1->gameObject);	
				// Add in collider list
				c2->colliders.add(c1);
			}
		}

		// Check if has collision exit in c1
		for (int i = 0, count = c1->colliders.count() ; i < count; i++)
		{
			// If not coll
			if(!c1->Intersects(c1->colliders[i]->rect))
			{
				// Collision exit
				c1->gameObject->OnCollisionExit(c1->colliders[i]->gameObject);
				// Remove in the collision list
				c1->colliders.remove(c1->colliders.At(i));
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
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr) continue;

		App->render->AddRectRenderQueue
			(colliders[i]->rect, // size
			colliders[i]->debugColor.r, 
			colliders[i]->debugColor.g,
			colliders[i]->debugColor.b,
			colliders[i]->debugColor.a,
				2); // layer
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr) RELEASE(colliders[i]);
	}

	return true;
}

void ModuleCollisions::AddCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			colliders[i] = collider;
			break;
		}
	}
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