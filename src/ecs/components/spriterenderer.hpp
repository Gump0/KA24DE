#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <string>
//---------------------------------------------------------------------------------
struct SpriteRenderer
{
    SDL_Texture* spriteTexture {nullptr};
    std::string imgLocation = "";
    int sizeX;
    int sizeY;
    // load flag (ez way to check if loaded or null)
    bool isLoaded {false};
};

#endif
