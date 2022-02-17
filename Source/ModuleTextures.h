#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__

#include <map>
#include <string>
#include "Module.h"
#include "List.h"

#define MAX_TEXTURES 50

struct SDL_Texture;

struct TexturePath
{
	std::string path = "";
	uint index = 0;
};

class ModuleTextures : public Module
{
public:
	// Constructor
	ModuleTextures();

	// Destructor
	~ModuleTextures();

	// Called on application start.
	// Initializes the SDL_Image library
	bool Start() override;

	// Called on application exit.
	// Frees the memory from all stored textures
	// Uninitializes the SDL_Image library
	bool CleanUp() override;

	// Loads a new SDL_Texture from a file path
	// First creates an SDL_Surface, then converts it into SDL_Texture
	// Returns nullptr if the texture could not be created
	SDL_Texture* const Load(const char* path);

	// Retrieve size of a texture by modifying parameters with and height
	void GetTextureSize(const SDL_Texture* texture, uint& width, uint& height) const;

public:
	// An array of all the loaded textures
	// Allows us to keep track of all textures and free them on application exit
	SDL_Texture* textures[MAX_TEXTURES] = { nullptr };

	List<TexturePath> texturePath;
};

#endif // __MODULETEXTURES_H__