#ifndef __RENDEROBJECT_H__
#define __RENDEROBJECT_H__

#include <string>

#include "SDL.h"
#include "Globals.h"

#include "Point.h"

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

	RenderType type; // render tipe of this render Object

	uint layer = 0;

	float orderInLayer = 0.0f;

	float scale = 1.0f;

	float speedRegardCamera = 1.0f;

	bool draw = true; // if want to draw this object

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

	SDL_Point rotCenter = { 0,0 };

#pragma endregion

public:
	RenderObject() {};

	~RenderObject() {};

	/// <summary>
	/// Initialize renderObject as Texture
	/// </summary>
	/// <param name="section"> : source rectangle or {0,0,0,0} for the entire texture </param>
	/// <param name="flip"> : enum of SDL_RendererFlip </param>
	/// <param name="speedRegardCamera"> : 0.0f = static texture on the screen , 1.0f = move with camera </param>
	void InitAsTexture(SDL_Texture* texture, iPoint position, SDL_Rect section = { 0,0,0,0 }, uint layer = 0, float orderInLayer = 0.0f,
		SDL_RendererFlip flip = SDL_FLIP_NONE, float rotation = 0.0f, float scale = 1.0f, float speedRegardCamera = 1.0f)
	{
		this->texture = texture;
		this->section = section;
		this->flip = flip;
		this->rotation = rotation;
		this->destRect.x = position.x;
		this->destRect.y = position.y;
		this->type = RENDER_TEXTURE;
		this->layer = layer;
		this->orderInLayer = orderInLayer;
		this->scale = scale;
		this->speedRegardCamera = speedRegardCamera;
		this->draw = true;
	}

	/// <summary>
	/// Initialize as Rectangle
	/// </summary>
	/// <param name="destRect"> position and dimension of the rectangle</param>
	/// <param name="speedRegardCamera"> : 0.0f = static texture on the screen , 1.0f = move with camera </param>
	void InitAsRect(SDL_Rect destRect, SDL_Color color = { 0,0,0,255 }, bool filled = false, int layer = 0, float orderInLayer = 0.0f,
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

	// To draw this renderObject
	bool Draw(SDL_Renderer* renderer)
	{
		if (!draw) return false;

		if (type == RENDER_TEXTURE) DrawTexture(renderer);
		else if (type == RENDER_RECT) DrawRect(renderer);

		return true;
	}

private:
	void DrawTexture(SDL_Renderer* renderer)
	{
		if (section.w == 0 || section.h == 0)
		{
			if (SDL_RenderCopyEx(renderer, texture, nullptr, &destRect, rotation, &rotCenter, flip) != 0)
			{
				LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			}
		}
		else
		{
			if (SDL_RenderCopyEx(renderer, texture, &section, &destRect, rotation, &rotCenter, flip) != 0)
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
};

#endif // !__RENDEROBJECT_H__