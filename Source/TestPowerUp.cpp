#include "TestPowerUp.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollisions.h"

TestPowerUp::TestPowerUp(iPoint pos, int* powerUps, bool bad):GameObject(pos,"powerUp")
{
	this->bad = bad;

	this->powerUps = powerUps;
	
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

	#pragma endregion
}

void TestPowerUp::OnCollisionEnter(GameObject* obj)
{
	// If we coll with player, and we aren't bad PowerUp, we die. Then scene powerUps--
	if (obj->name == "player" && !bad)
	{
		pendingToDelete = true;
		(*powerUps)--;
	}
}
