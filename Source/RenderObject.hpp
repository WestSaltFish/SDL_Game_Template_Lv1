#ifndef __RENDEROBJECT_H__
#define __RENDEROBJECT_H__

#include <string>

#include "External/SDL/include/SDL.h"
#include "Globals.h"

enum RenderType
{
	RENDER_TEXTURE,
	RENDER_RECT
};

class RenderObject
{
public:

	#pragma region Global Properties

	std::string name = "renderObject";

	SDL_Rect destRect = { 0,0,0,0 };

	RenderType type;

	uint layer = 0;

	float orderInLayer = 0.0f;

	float scale = 1.0f;

	float speedRegardCamera = 1.0f;

	bool draw = false; // if want to draw this object

	#pragma endregion

	#pragma region Rect properties

	SDL_Color color = { 0,0,0,0 };

	bool filled = true;

	#pragma endregion

	#pragma region Texture properties

	SDL_Texture* texture = nullptr;

	SDL_Rect section = { 0,0,0,0 };

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	float rotation = 0.0f;

	int textureCenterX = 0;

	int textureCenterY = 0;

	#pragma endregion

public:

	RenderObject() {};

	~RenderObject() {};

	bool Draw(SDL_Renderer* renderer)
	{
		if (!draw) return true;

		if (type == RENDER_TEXTURE)
		{
			DrawTexture(renderer);
		}
		else if (type == RENDER_RECT)
		{
			DrawRect(renderer);
		}
	}

	void DrawTexture(SDL_Renderer* renderer)
	{
		if (section.w == 0 || section.h == 0)
		{
			if (SDL_RenderCopyEx(renderer, texture, nullptr, &destRect, rotation, NULL, flip) != 0)
			{
				LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			}
		}
		else
		{
			if (SDL_RenderCopyEx(renderer, texture, &section, &destRect, rotation, NULL, flip) != 0)
			{
				LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			}
		}
	}

	void DrawRect(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

		if (filled)
		{
			SDL_RenderFillRect(renderer, &destRect);
		}
		else
		{
			SDL_RenderDrawRect(renderer, &destRect);
		}
	}

	void InitAsTexture(SDL_Texture* texture, SDL_Rect destRect, SDL_Rect section = {0,0,0,0}, uint layer = 0, float orderInLayer = 0.0f,
		SDL_RendererFlip flip = SDL_FLIP_NONE, float rotation = 0.0f, float scale = 1.0f, float speedRegardCamera = 1.0f)
	{
		this->texture = texture;
		this->section = section;
		this->flip = flip;
		this->rotation = rotation;
		this->destRect = destRect;
		this->type = RENDER_TEXTURE;
		this->layer = layer;
		this->orderInLayer = orderInLayer;
		this->scale = scale;
		this->speedRegardCamera = speedRegardCamera;
		this->draw = true;
	}

	void InitAsRect(SDL_Rect destRect, SDL_Color color = { 0,0,0,255 }, bool filled = false, int ulayer = 0, float orderInLayer = 0.0f,
		float speedRegardCamera = 1.0f)
	{
		this->color = color;
		this->filled = filled;
		this->destRect = destRect;
		this->type = RENDER_RECT;
		this->layer = layer;
		this->orderInLayer = orderInLayer;
		this->scale = scale;
		this->speedRegardCamera = speedRegardCamera;
		this->draw = true;
	}
};

#endif // !__RENDEROBJECT_H__