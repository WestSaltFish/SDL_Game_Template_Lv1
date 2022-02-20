#include "Application.h"

#include <time.h> 
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleScene.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		new ModuleWindow();
	modules[1] =	input =			new ModuleInput();
	modules[2] =	textures =		new ModuleTextures();
	modules[3] =	audio =			new ModuleAudio();
	modules[4] =	scene =			new ModuleScene();
	modules[5] =	collisions =	new ModuleCollisions();
	modules[6] =	render =		new ModuleRender();

	// Init random seed;
	srand(time(NULL));
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		// WARNING: When deleting a pointer, set it to nullptr afterwards
		// It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// All modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Start();

	return ret;
}

UpdateResult Application::Update()
{
	// Get frame time in ms
	uint startFrame = SDL_GetTicks();

	UpdateResult ret = UpdateResult::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PreUpdate();

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->Update();

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PostUpdate();

	// Get current frame time in ms
	uint currentFrameTime = SDL_GetTicks() - startFrame;

	printf("%d\n", SDL_GetTicks());

	// If this frame is 
	if (currentFrameTime < frameTime)
	{
		SDL_Delay(frameTime -currentFrameTime);
	}

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->CleanUp();

	return ret;
} 