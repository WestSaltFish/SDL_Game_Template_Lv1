#include "PlayerDieParticle.h"
#include "Application.h"
#include "ModuleTextures.h"

PlayerDieParticle::PlayerDieParticle(iPoint position, float life, float delay) :Particle(position, life, delay)
{
	#pragma region Init RenderObject

	SDL_Texture* tex = App->textures->Load("Assets/Images/DinoSprites-vita24x24.png");

	renderObjects[0].InitAsTexture(tex, { position.x,position.y, 24, 24}, { 0,0,24,24 }, 1, 0);

	#pragma endregion

	#pragma region Init Animations

	for (int i = 0; i < 3; i++)
	{
		anim.PushBack({ 24 * i, 48, 24, 24 });
	}
	anim.speed = 0.2f;

	anim.loop = false;

	#pragma endregion
}