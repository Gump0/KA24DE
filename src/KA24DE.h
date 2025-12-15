// base c++ standard stuff
#include <SDL3/SDL_filesystem.h>
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

//---------------------------------------------------------------------------------
class KA24DE
{
public:
    KA24DE();
    ~KA24DE();

    // window
    const int gScreenWidth {1280};
    const int gScreenHeight {720};
    SDL_Window* gWindow {nullptr};

    // renderer
    SDL_Renderer* gRenderer {nullptr};

    // time
    float deltaTime;
    float frameRate;

    bool init();        // called on program start
    void start();       // "start code" for user to initialize gameplay code after engine inits
    bool render();      // handles SDL render calls
    void update();      // handles game-loop
    void shutDown();    // handles memory cleanup of program

private:
};
