#include "ModuleRender.h"

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

#include "External/SDL/include/SDL_render.h"
#include "External/SDL/include/SDL_scancode.h"

ModuleRender::ModuleRender(bool startEnabled) : Module(startEnabled)
{
	camera.x = camera.y = 0;

	renderLayers.resize(MAX_LAYERS);
}

ModuleRender::~ModuleRender()
{

}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;	
	Uint32 flags = 0;

	if (VSYNC == true) flags |= SDL_RENDERER_PRESENTVSYNC;

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// L10: DONE: Set render logical size
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	return ret;
}

// Called every draw update
UpdateResult ModuleRender::PreUpdate()
{
	// Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Clear rendering target
	SDL_RenderClear(renderer);

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleRender::Update()
{
	// Handle positive vertical movement
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_REPEAT) camera.y -= cameraSpeed;

	// Handle negative vertical movement
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_REPEAT) camera.y += cameraSpeed;

	// L4: DONE 1: Handle horizontal movement of the camera
	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_REPEAT) camera.x -= cameraSpeed;
	if (camera.x < 0) camera.x = 0;

	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT) camera.x += cameraSpeed;

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleRender::PostUpdate()
{
	// Sorting layers
	for (int i = 0; i < renderLayers.size(); ++i)
	{
		if(renderLayers[i].sort) SortingObjectsInLayer(renderLayers[i].renderObjects);
	}

	//Draw
	for (int i = 0; i < MAX_LAYERS; ++i)
	{
		for (int j = 0, length = renderLayers[i].renderObjects.size(); j < length; j++)
		{
			renderLayers[i].renderObjects[j].Draw(renderer);
		}
	}

	// Update the screen
	SDL_RenderPresent(renderer);

	// Clear layers
	ClearRederQueue();

	return UpdateResult::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	// Destroy the rendering context
	if (renderer != nullptr) SDL_DestroyRenderer(renderer);

	return true;
}

void ModuleRender::AddTextureRenderQueue(SDL_Texture* texture, iPoint pos, SDL_Rect section, float scale, int layer, float orderInlayer, float rotation, SDL_RendererFlip flip, float speed)
{
	RenderObject renderObject;

	SDL_Rect destRect = { 0,0 };

	if (uiLayer >= 0 && layer == uiLayer)
	{
		//If texture in UI layer, it moves alongside the camera-> , speed = 0;
		speed = 0;
	}

	renderObject.InitAsTexture(texture, destRect, section, layer, orderInlayer, flip, rotation, scale, speed);

	renderObject.destRect.x = (int)(-camera.x * speed) + pos.x * App->window->scale;
	renderObject.destRect.y = (int)(-camera.y * speed) + pos.y * App->window->scale;

	if (section.h != 0 && section.w != 0)
	{
		renderObject.destRect.w = section.w;
		renderObject.destRect.h = section.h;
	}
	else
	{
		// Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &renderObject.destRect.w, &renderObject.destRect.h);
	}

	renderObject.destRect.w *= scale * App->window->scale;
	renderObject.destRect.h *= scale * App->window->scale;

	renderLayers[layer].renderObjects.push_back(renderObject);
}

void ModuleRender::AddRectRenderQueue(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int layer, float orderInlayer, bool filled, float speed)
{
	RenderObject renderObject;

	SDL_Rect rec = 
	{ (-camera.x * speed) + rect.x * App->window->scale, (-camera.y * speed) + rect.y * App->window->scale,
		rect.w * App->window->scale, rect.h * App->window->scale };

	renderObject.InitAsRect(rec, { r,g,b,a }, filled, layer, orderInlayer, speed);

	if (uiLayer >= 0 && renderObject.layer == uiLayer)
	{
		//If texture in UI layer, it moves alongside the camera-> , speed = 0;
		renderObject.speedRegardCamera = 0;
	}

	renderLayers[layer].renderObjects.push_back(renderObject);
}

void ModuleRender::AddRenderObjectRenderQueue(RenderObject renderObject)
{
	if (uiLayer >= 0 && renderObject.layer == uiLayer)
	{
		//If texture in UI layer, it moves alongside the camera-> , speed = 0;
		renderObject.speedRegardCamera = 0;
	}

	renderLayers[renderObject.layer].renderObjects.push_back(renderObject);
}

void ModuleRender::SortingObjectsInLayer(std::vector<RenderObject>& objects)
{
	int less = 0;
	int objSize = objects.size();

	for (int i = 0; i < objSize; ++i)
	{
		less = i;
		for (int j = i; j < objSize; ++j)
		{
			if (objects[j].orderInLayer < objects[less].orderInLayer)
			{
				std::swap(objects[j], objects[less]);
			}
		}
	}
}

void ModuleRender::ClearRederQueue()
{
	for (int i = 0; i < MAX_LAYERS; i++)
	{
		renderLayers[i].renderObjects.clear();
	}
}

#pragma region OBSOLETE
// Draw to screen
bool ModuleRender::DrawTexture(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed, bool useCamera)
{
	bool ret = true;

	SDL_Rect dstRect{ x * SCREEN_SIZE, y * SCREEN_SIZE, 0, 0 };

	if (useCamera)
	{
		dstRect.x -= (camera.x * speed);
		dstRect.y -= (camera.y * speed);
	}

	if (section != nullptr)
	{
		dstRect.w = section->w;
		dstRect.h = section->h;
	}
	else
	{
		// Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);
	}

	dstRect.w *= SCREEN_SIZE;
	dstRect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &dstRect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawRectangle(const SDL_Rect& rect, SDL_Color color, float speed, bool useCamera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Rect dstRect { rect.x * SCREEN_SIZE, rect.y * SCREEN_SIZE, rect.w * SCREEN_SIZE, rect.h * SCREEN_SIZE };

	if (useCamera)
	{
		dstRect.x -= (camera.x * speed);
		dstRect.y -= (camera.y * speed);
	}

	if (SDL_RenderFillRect(renderer, &dstRect) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}
#pragma endregion