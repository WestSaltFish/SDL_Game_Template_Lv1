#ifndef _TEXT_
#define _TEXT_

#include "GameObject.h"
#include "ModuleFonts.h"

class Text : public GameObject
{
public:
	Text(iPoint pos, std::string text, FontsEnum font = FontsEnum::ADVANCED_PIXEL, SDL_Color color = {255,0,0,255});

	~Text();

	void ChangeText(std::string text);

	void ChangeFont(FontsEnum font);

	/// <summary>
	/// Changes renderObject scale, not font size. To change font size use ChangeFont() with a different sized font.
	/// </summary>
	/// <param name="size"></param>
	void ChangeScale(uint scale);

	void ChangeColor(SDL_Color color);

private:
	void CreateTexture();

	std::string m_Text;
	FontsEnum currentFont;
	SDL_Color currentColor;
};

#endif
