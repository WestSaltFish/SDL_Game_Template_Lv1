#include "Text.h"
#include "Application.h"
#include "ModuleRender.h"

Text::Text(iPoint pos, std::string text, FontsEnum font, SDL_Color color) : GameObject(pos, "Text")
{
	this->currentFont = font;
	this->currentColor = color;
	this->m_Text = text;

	CreateTexture();

	this->renderObjects->layer = 3;
}

Text::~Text()
{
	if (renderObjects[0].texture)
	{
		SDL_DestroyTexture(renderObjects[0].texture);
	}
}

void Text::ChangeText(std::string text)
{
	this->m_Text = text;
	CreateTexture();
}

void Text::ChangeFont(FontsEnum font)
{
	this->currentFont = font;
	CreateTexture();
}

void Text::ChangeScale(uint scale)
{
	renderObjects[0].scale = scale;
}

void Text::ChangeColor(SDL_Color color)
{
	this->currentColor = color;
	CreateTexture();
}

void Text::CreateTexture()
{
	if (renderObjects[0].texture)
	{
		SDL_DestroyTexture(renderObjects[0].texture);
	}

	TTF_Font* font = App->fonts->GetFont(this->currentFont);

	SDL_Surface* s = TTF_RenderText_Solid(font, m_Text.c_str(), currentColor);

	this->renderObjects[0].texture = SDL_CreateTextureFromSurface(App->render->renderer, s);

	SDL_FreeSurface(s);
}
