///////////////////////////////////////////
// handles the rendering of entities
// with 2d sprite renderer components
// requires (transform, sprite renderer)
///////////////////////////////////////////
#ifndef SPRITE_RENDERING_SYSTEM_H
#define SPRITE_RENDERING_SYSTEM_H

#include "../system.hpp"
#include "../components/spriterenderer.hpp"
#include <SDL3/SDL_render.h>
#include <string>
//---------------------------------------------------------------------------------
class SpriteRenderingSystem : public System
{
public:
    void Init();
    void Render(SDL_Renderer* renderer);
    bool LoadSprite(SpriteRenderer& sr, SDL_Renderer* renderer);
private:
    std::string AssetPath()
    {
        std::string base(SDL_GetBasePath());
        return base + "../assets/";
    };
};

#endif
