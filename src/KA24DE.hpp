////////////////////////////////////////////////////////////
// class file that will manage the construction of systems,
// game-engine initialization, game-loop and rendering.
////////////////////////////////////////////////////////////
#ifndef KA24DE_H
#define KA24DE_H

//---------------------------------------------------------------------------------
// sdl
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_filesystem.h>

// time library
#include <chrono>
#include <memory>

// input manager
#include "input-manager/input.hpp"

// ecs dictator class
#include "ecs/dictator.hpp"

//---------------------------------------------------------------------------------

// ecs dictator
extern Dictator gDictator;

class KA24DE
{
    SpriteRenderingSystem* spriteRenderingSystem {nullptr};
    CollisionSystem* collisionSystem {nullptr};
    ScriptingLayer* scriptingLayer {nullptr};

public:
    KA24DE();           // class constructor
    ~KA24DE();          // destructor that handles memory cleanup of program

    // time
    double deltaTime;

    bool init();        // called on program start
    void start();       // "start code" for user to initialize gameplay code after engine inits
    bool render();      // handles SDL render calls
    void update();      // handles game-loop
    void shutDown();    // handles memory cleanup of program

private:
// window
const int mScreenWidth {1280};
const int mScreenHeight {720};
SDL_Window* mWindow {nullptr};

// renderer
SDL_Renderer* mRenderer {nullptr};

// engine time
using engineClock = std::chrono::steady_clock;
};

#endif
