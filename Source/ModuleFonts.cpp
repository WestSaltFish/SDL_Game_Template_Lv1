#include "ModuleFonts.h"

ModuleFonts::ModuleFonts() : Module()
{
}

bool ModuleFonts::Start()
{  
    TTF_Init();

    // Default font
    TTF_Font* advancedPixelFont = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 32);

    if (!advancedPixelFont) 
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    fonts.push_back(advancedPixelFont);

    // Default font 2
    TTF_Font* oldLondonFont = TTF_OpenFont("Assets/Fonts/old_london.ttf", 32);

    if (!oldLondonFont) 
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    fonts.push_back(oldLondonFont);

    return true;
}

bool ModuleFonts::CleanUp()
{
    for (int i = 0; i < fonts.size(); i++)
    {
        TTF_CloseFont(fonts[i]);
        fonts[i] = nullptr;
    }

    fonts.clear();

    TTF_Quit();

    return true;
}