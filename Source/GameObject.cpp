#include "GameObject.h"
#include "Application.h"
#include "ModuleCollisions.h"

GameObject::GameObject(iPoint position, std::string name)
{
	this->name = name;
	this->position = position;
}

GameObject::~GameObject()
{
	if (renderObject != nullptr)
	{
		delete renderObject;
		renderObject = nullptr;
	}

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


