#ifndef __MENU_TEXT_H__
#define __MENU_TEXT_H__

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

#endif // !__MENU_TEXT_H__