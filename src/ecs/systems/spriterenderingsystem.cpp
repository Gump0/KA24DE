#include "spriterenderingsystem.hpp"
#include "../components/transform.hpp"
#include "../../KA24DE.hpp"
#include <SDL3/SDL_log.h>

void SpriteRenderingSystem::Init() { }
// TODO :
// remove the need to call GetComponent every frame
// and remember what individual entity has certain components anb adapt to any change during runntime

void SpriteRenderingSystem::Render(SDL_Renderer* renderer)
{
    for(auto const& entity : mEntities)
    {
        // grab references
        auto& sr = gDictator.GetComponent<SpriteRenderer>(entity);
        auto& transform = gDictator.GetComponent<Transform>(entity);

        // sdl rendering logic here cuh
        if(!sr.isLoaded)
            LoadSprite(sr, renderer);

        if(!sr.spriteTexture)
        {
            SDL_Log("ERROR : Texture was not initialized in sprite renderer component %s:", SDL_GetError());
            continue;
        }

        SDL_FRect dst
        {
            // TODO : Include rotation
            transform.PosX,
            transform.PosY,
            sr.sizeX * transform.ScaleX,
            sr.sizeY * transform.ScaleY,
        };

        SDL_RenderTexture(renderer, sr.spriteTexture, nullptr, &dst);
    }
}

bool SpriteRenderingSystem::LoadSprite(SpriteRenderer& sr, SDL_Renderer* renderer)
{
    if(sr.isLoaded)
        return true;

    std::string path = AssetPath() + sr.imgLocation;
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if(!surface)
    {
        SDL_Log("ERROR : Loading sprite %s: %s", path.c_str(), SDL_GetError());
        return false;
    }

    sr.spriteTexture = SDL_CreateTextureFromSurface(renderer, surface);
    sr.sizeX = surface->w;
    sr.sizeY = surface->h;

    SDL_DestroySurface(surface);

    sr.isLoaded = sr.spriteTexture != nullptr;
    return sr.isLoaded;
}
