#include "TestPowerUp.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollisions.h"

TestPowerUp::TestPowerUp(iPoint pos, bool bad):GameObject(pos,"powerUp")
{
	this->bad = bad;
	
	#pragma region Init RenderObject

	SDL_Texture* tex = nullptr;

	if(bad)
	tex = App->textures->Load("Assets/Images/PowerUp2.png");
	else
	tex = App->textures->Load("Assets/Images/PowerUp1.png");

	renderObjects[0].InitAsTexture(tex, { position.x,position.y,8,8 }, { 0,0,0,0 }, 1, 1);

	#pragma endregion

	#pragma region Init Collision

	col = new Collider({ pos.x,pos.y, 8,8 }, this, "PowerUp");

	App->collisions->AddCollider(col);

	#pragma endregion
}
