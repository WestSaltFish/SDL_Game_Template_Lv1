#include "ModuleRender.h"

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

#include "External/SDL/include/SDL_render.h"
#include "External/SDL/include/SDL_scancode.h"

ModuleRender::ModuleRender() : Module()
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

	// Active sorting
	renderLayers[1].sort = true;

	return ret;
}

// Called every draw update
UpdateResult ModuleRender::PreUpdate()
{
	// Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Clear rendering target
	SDL_RenderClear(renderer);

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleRender::Update()
{
	// Camera movement
	/*
	// Handle positive vertical movement
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_REPEAT) camera.y -= cameraSpeed;

	// Handle negative vertical movement
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_REPEAT) camera.y += cameraSpeed;

	// L4: DONE 1: Handle horizontal movement of the camera
	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_REPEAT) camera.x -= cameraSpeed;
	if (camera.x < 0) camera.x = 0;

	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT) camera.x += cameraSpeed;
	*/

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

	ClearRederQueue();

	// Destroy the rendering context
	if (renderer != nullptr) SDL_DestroyRenderer(renderer);

	return true;
}

void ModuleRender::AddTextureRenderQueue(SDL_Texture* texture, iPoint pos, SDL_Rect section, float scale, uint layer, float orderInlayer, float rotation, SDL_RendererFlip flip, float speed)
{
	RenderObject renderObject;

	SDL_Rect destRect = { 0,0 };

	// Limit layer in the range
	layer = layer > topLayer ? topLayer : layer;

	//If texture in UI layer, it moves alongside the camera-> , speed = 0;
	if (topLayer >= 0 && layer == topLayer) speed = 0;

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

void ModuleRender::AddRectRenderQueue(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, uint layer, float orderInlayer, bool filled, float speed)
{
	RenderObject renderObject;

	// Limit layer in the range
	layer = layer > topLayer ? topLayer : layer;

	//If texture in UI layer, it moves alongside the camera-> , speed = 0;
	if (layer == topLayer )speed = 0;

	SDL_Rect rec = 
	{ (-camera.x * speed) + rect.x * App->window->scale, (-camera.y * speed) + rect.y * App->window->scale,
		rect.w * App->window->scale, rect.h * App->window->scale };

	renderObject.InitAsRect(rec, { r,g,b,a }, filled, layer, orderInlayer, speed);

	renderLayers[layer].renderObjects.push_back(renderObject);
}

void ModuleRender::AddRenderObjectRenderQueue(RenderObject renderObject)
{

	// Limit layer in the range
	renderObject.layer = renderObject.layer > topLayer ? topLayer : renderObject.layer;

	if (renderObject.layer == topLayer)
	{
		//If texture in UI layer, it moves alongside the camera-> , speed = 0;
		renderObject.speedRegardCamera = 0;
	}

	renderObject.destRect.x = (int)(-camera.x * renderObject.speedRegardCamera) + renderObject.destRect.x * App->window->scale;
	renderObject.destRect.y = (int)(-camera.y * renderObject.speedRegardCamera) + renderObject.destRect.y * App->window->scale;

	if (renderObject.section.h != 0 && renderObject.section.w != 0)
	{
		renderObject.destRect.w = renderObject.section.w;
		renderObject.destRect.h = renderObject.section.h;
	}
	else
	{
		// Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(renderObject.texture, nullptr, nullptr, &renderObject.destRect.w, &renderObject.destRect.h);
	}

	renderObject.destRect.w *= renderObject.scale * App->window->scale;
	renderObject.destRect.h *= renderObject.scale * App->window->scale;

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