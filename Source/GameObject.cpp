#include "GameObject.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleScene.h"

GameObject::GameObject(iPoint position, std::string name)
{
	this->name = name;
	this->position = position;

	AddtoList();
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
	if (col != nullptr) col->SetPos(position.x, position.y);
}

void GameObject::PostUpdate()
{
	// Draw textures
	for (int i = 0; i < MAX_RENDEROBJECT; i++)
	{
		if (renderObjects[i].type == RenderType::RENDER_TEXTURE && !renderObjects[i].texture) continue;

		if (renderObjects[i].draw)
		{
			renderObjects[i].destRect.x = position.x;
			renderObjects[i].destRect.y = position.y;

			App->render->AddRenderObjectRenderQueue(renderObjects[i]);
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


void GameObject::AddtoList()
{
	App->scene->scenes[App->scene->currentSceneIndex]->AddGameObject(this);
}
