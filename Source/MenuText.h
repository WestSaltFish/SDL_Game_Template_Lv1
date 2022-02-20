#pragma once

struct SDL_Texture;

class MenuText 
{
public:
	MenuText();

	void Update();

	void PostUpdate();

private:
	SDL_Texture* optionsTexture = nullptr;
};

