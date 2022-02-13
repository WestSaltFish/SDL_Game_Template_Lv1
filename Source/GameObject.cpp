#include "GameObject.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

GameObject::GameObject(iPoint position, std::string name)
{
	this->name = name;
	this->position = position;
}

GameObject::~GameObject()
{
	if (col != nullptr)
	{
		App->collisions->RemoveCollider(col);
		col = nullptr;
	}
}

void GameObject::Start()
{
}

void GameObject::PreUpdate()
{
}

void GameObject::Update()
{
	// Update collision position with this.position
	col->SetPos(position.x, position.y);
}

void GameObject::PostUpdate()
{
	// Dibujar texturas
	for (int i = 0; i < MAX_TEXTURES; i++)
	{
		if (renderObjects[i].texture != nullptr && renderObjects[i].draw)
		{
			renderObjects[i].destRect.x = position.x;
			renderObjects[i].destRect.y = position.y;

			App->render->AddRenderObjectRenderQueue(renderObjects[i]);

			/*App->render->AddTextureRenderQueue(renderObjects[i].texture, { renderObjects[i].destRect.x,renderObjects[i].destRect.y },
				renderObjects[i].section, renderObjects[i].scale, renderObjects[i].layer, renderObjects[i].orderInLayer,
				renderObjects[i].rotation, renderObjects[i].flip, renderObjects[i].speedRegardCamera);*/
		}
	}
}

void GameObject::OnCollisionEnter(GameObject* g)
{
}

void GameObject::OnCollisionExit(GameObject* g)
{
}

void GameObject::CleanUp()
{
}