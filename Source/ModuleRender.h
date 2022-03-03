#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include <vector>

#include "Module.h"
#include "RenderObject.hpp"
#include "Point.h"

// Must have more than 3
#define MAX_LAYERS 4

struct SDL_Color;
struct SDL_Texture;
struct SDL_Renderer;

struct RenderLayer
{
	// IMPORTANT: if you activate it, it will start sorting from this layer
	bool sort = false;
	std::vector<RenderObject> renderObjects;
};

class ModuleRender : public Module
{
public:
	// Constructor
	ModuleRender();

	// Destructor
	~ModuleRender();

	// Called on application start.
	// Creates the rendering context using the program's window.
	bool Init() override;

	// Called at the beginning of the application loop
	// Clears the rendering context to a background color
	UpdateResult PreUpdate() override;

	// Called at the middle of the application loop
	// Handles camera movement
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Displays a rectangle in the rendering context
	// Updates the screen with the rendered content
	UpdateResult PostUpdate() override;

	// Called on application exit.
	// Destroys the rendering context
	bool CleanUp() override;

	/// <summary>
	/// Add a specific texture in the render queue
	/// </summary>
	/// <param name="texture">: texture you want to draw</param>
	/// <param name="pos">: renderObject position in the screen</param>
	/// <param name="section">: the section you want to capture in this texture, if you want the whole image enter {0,0,0,0}</param>
	/// <param name="scale">: scale of renderObject in screen</param>
	/// <param name="layer">: layer of renderObject, must be positive</param>
	/// <param name="orderInlayer">: order of renderObject in his layer</param>
	/// <param name="rotation">: renderObject rotation</param>
	/// <param name="flip">: if you want to flip the image, use SDL_FLIP_HORIZONAL or SDL_FLIP_VERTICAL</param>
	/// <param name="speed">: relative speed between renderObject and camera, 0 = stays fixed on the screen, 1 = synchronizes camera movement 100%/param>
	void AddTextureRenderQueue(SDL_Texture* texture, iPoint pos, SDL_Rect section = { 0,0,0,0 },
		float scale = 1, uint layer = 0, float orderInlayer = 0.0f, float rotation = 0, 
		SDL_RendererFlip flip = SDL_FLIP_NONE, float speed = 1.0f);

	/// <summary>
	/// Add a specific rect in the render queue
	/// </summary>
	/// <param name="rect">: the rect you want to draw</param>
	/// <param name="r">: color.r</param>
	/// <param name="g">: color.r</param>
	/// <param name="b">: color.b</param>
	/// <param name="a">: color.a</param>
	/// <param name="layer">: layer of renderObject, must be positive</param>
	/// <param name="orderInlayer">: order of renderObject in his layer</param>
	/// <param name="filled">: determine whether the rect is to be filled or not</param>
	/// <param name="speed">: relative speed between renderObject and camera, 0 = stays fixed on the screen, 1 = synchronizes camera movement 100%</param>
	void AddRectRenderQueue(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255,
		uint layer = 1, float orderInlayer = 0.0f, bool filled = true, float speed = 1.0f);

	void AddRenderObjectRenderQueue(RenderObject renderObject);

	/// <summary>
	/// Sort the layer that has passed
	/// </summary>
	/// <param name="layer"></param>
	void SortingObjectsInLayer(std::vector<RenderObject>& layer);

	void ClearRederQueue();
public:
	// Rendering context used for any rendering action
	SDL_Renderer* renderer = nullptr;

	// A rectangle that represents the camera section
	// Sprites will be rendered to the screen depending on the camera position
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// The speed at which the camera will be moving
	int cameraSpeed = 3;

	// The top layer
	int topLayer = MAX_LAYERS - 1;

private:
	std::vector<RenderLayer> renderLayers;
};

#endif //__MODULERENDER_H__
