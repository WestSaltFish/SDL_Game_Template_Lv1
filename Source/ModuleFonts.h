#ifndef _MODULE_FONTS_
#define _MODULE_FONTS_

#include "Module.h"
#include "SDL_ttf.h"

#include <vector>

enum class FontsEnum
{
	ADVANCED_PIXEL = 0,
	OLD_LONDON,
};

class ModuleFonts : public Module
{
public:
	ModuleFonts();

	bool Start() override;

	TTF_Font* GetFont(uint index)
	{
		if (index > fonts.size() - 1) return nullptr;

		return fonts[index];
	}

	TTF_Font* GetFont(FontsEnum index)
	{
		if ((uint)index > fonts.size() - 1) return nullptr;

		return fonts[(uint)index];
	}

	bool CleanUp() override;

private:
	std::vector<TTF_Font*> fonts;
};

#endif