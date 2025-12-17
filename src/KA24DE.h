#ifndef KA24DE_H
#define KA24DE_H
// base c++ standard stuff
#include "input-manager/input.h"
#include <atomic>
#include <iostream>
#include <string>

//---------------------------------------------------------------------------------
// sdl
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_filesystem.h>

//---------------------------------------------------------------------------------
class KA24DE
{
public:
    KA24DE();           // class constructor
    ~KA24DE();          // destructor that handles memory cleanup of program

    // time
    float deltaTime;
    float frameRate;

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
};

#endif
