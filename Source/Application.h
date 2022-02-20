#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 7

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModuleScene;
class ModuleCollisions;
class ModuleRender;

class Application
{
public:
	// Constructor. Creates all necessary modules for the application
	Application();

	// Destructor. Removes all module objects
	~Application();

	// Initializes all modules
	bool Init();

	// Updates all modules (PreUpdate, Update and PostUpdate)
	UpdateResult Update();

	// Releases all the application data
	bool CleanUp();

public:

	// Array to store the pointers for the different modules
	Module* modules[NUM_MODULES] = { nullptr };

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModuleScene* scene = nullptr;

	ModuleCollisions* collisions = nullptr;

	ModuleRender* render = nullptr;

	// Frame time in ms
	uint frameTime = (1.0 / 60.0) * 1000;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__