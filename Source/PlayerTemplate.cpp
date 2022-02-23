#include "PlayerTemplate.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "PlayerDieParticle.h"
#include "TestPowerUp.h"

PlayerTemplate::PlayerTemplate(iPoint pos, std::string name) :GameObject(pos, name)
{
	//You can init this game object here

	#pragma region Init RenderObject

	// Player
	SDL_Texture* tex = App->textures->Load("Assets/Images/DinoSprites-vita24x24.png");
	renderObjects[0].InitAsTexture(tex, { position.x,position.y,24,24 }, { 0,0,24,24 }, 1, 2);
	
	// Shadow
	SDL_Texture* tex2 = App->textures->Load("Assets/Images/shadow_24x24.png");
	renderObjects[1].InitAsTexture(tex2, { position.x,position.y,24,24 }, { 0,0,24,24 }, 1, 0);

	#pragma endregion

	#pragma region Init Animations

	// Idle
	for (int i = 0; i < 4; i++)
	{
		idle.PushBack({ 24 * i, 0, 24, 24 });
	}
	idle.speed = 0.2f;

	// Move
	for (int i = 0; i < 6; i++)
	{
		move.PushBack({ 24 * i, 24, 24, 24 });
	}
	move.speed = 0.2f;

	#pragma endregion

	#pragma region Init Collision

	col = new Collider({ pos.x,pos.y, 18,24 }, this, "Player", { 3, 0});

	#pragma endregion
}

PlayerTemplate::~PlayerTemplate()
{
	
}

void PlayerTemplate::Start()
{

}

void PlayerTemplate::PreUpdate()
{

}

void PlayerTemplate::Update()
{
	if (App->input->keys[SDL_SCANCODE_O] == KEY_DOWN)
	{
		Die();
	}

	if(!moveBlock)
	Movement();

	GameObject::Update();
}

void PlayerTemplate::PostUpdate()
{
	Animations();

	GameObject::PostUpdate();
}

void PlayerTemplate::CleanUp()
{
}

void PlayerTemplate::OnCollisionEnter(GameObject* g)
{
	if (g->name == "powerUp")
	{
		TestPowerUp* t = (TestPowerUp*)g;

		// If this powerUp is bad, we die
		if (t->bad)
		{
			Die();
		}
	}
}

void PlayerTemplate::Die()
{
	pendingToDelete = true;
	new PlayerDieParticle(this->position);
}

void PlayerTemplate::Movement()
{
	// Rushing out the code
	// DON'T LEARN !!!

	// Get current position
	iPoint nextPos = position;

	// Vertical movement
	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
	{
		nextPos.y -= speed;

		if(renderObjects[0].flip == SDL_FLIP_HORIZONTAL)
			state = PlayerStates::MOVE_LEFT;
		else
			state = PlayerStates::MOVE_RIGHT;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
	{
		nextPos.y += speed;

		if (renderObjects[0].flip == SDL_FLIP_HORIZONTAL)
			state = PlayerStates::MOVE_LEFT;
		else
			state = PlayerStates::MOVE_RIGHT;
	}
	else if (App->input->keys[SDL_SCANCODE_W] == KEY_UP || App->input->keys[SDL_SCANCODE_S] == KEY_UP)
	{
		state = PlayerStates::IDLE;
	}

	// Horizontal movement
	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		nextPos.x -= speed;
		renderObjects[0].flip = SDL_FLIP_HORIZONTAL;
		state = PlayerStates::MOVE_LEFT;
	}
	else if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		nextPos.x += speed;
		renderObjects[0].flip = SDL_FLIP_NONE;
		state = PlayerStates::MOVE_RIGHT;
	}	
	else if(App->input->keys[SDL_SCANCODE_D] == KEY_UP || App->input->keys[SDL_SCANCODE_A] == KEY_UP)
	{
		state = PlayerStates::IDLE;
	}

	// A simple border limitation
	if (nextPos.x > 5 && nextPos.x < 350)
	{
		// Move player in X axis
		position.x = nextPos.x;
	}
	if(nextPos.y > 5 && nextPos.y < 220)
	{
		// Move player in Y axis
		position.y = nextPos.y;
	}
}

void PlayerTemplate::Animations()
{
	switch (state)
	{
	case PlayerStates::IDLE:
		idle.Update();
		renderObjects[0].section = idle.GetCurrentFrame();
		break;
	case PlayerStates::MOVE_LEFT:
		move.Update();
		renderObjects[0].section = move.GetCurrentFrame();
		break;
	case PlayerStates::MOVE_RIGHT:
		move.Update();
		renderObjects[0].section = move.GetCurrentFrame();
		break;
	}
}
