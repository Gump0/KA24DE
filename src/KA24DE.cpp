/////////////////////////////////////////////////////////////////////////////////////////////////////
// class file that will manage the construction of global variables, system classes and destruction.
/////////////////////////////////////////////////////////////////////////////////////////////////////
#include "KA24DE.h"

KA24DE::KA24DE()
{
}

KA24DE::~KA24DE()
{
    // cleanup objects
    // e.g delete cameraManager

    shutDown();
}

bool KA24DE::init()
{
    bool success {true};
    if(SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log("SDL could not initalize video! SDL error: %s\n", SDL_GetError());
        success = false;
    }

    if(!SDL_CreateWindowAndRenderer( "TGE : WIP name and code lol",
        gScreenWidth, gScreenHeight, SDL_WINDOW_MAXIMIZED,
        &gWindow, &gRenderer ))
    {
        SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
        success = false;
    }
    return success;
}

void KA24DE::start()
{
    // "start code" to garuntee running after engine initalizes
    // probably going to be used of user scripts
}

bool KA24DE::render()
{
    // render logic ^^
    bool success {true};

    return success;
}

void KA24DE::update()
{
    bool quit {false};
    SDL_Event e;
    SDL_zero(e);

    while(quit == false)
    {
        while(SDL_PollEvent(&e) == true)
        {
            if(e.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 230, 115, 0, 255);
        SDL_RenderClear(gRenderer);
        SDL_RenderPresent(gRenderer);
    }
}

void KA24DE::shutDown()
{
    // cleanup program.
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_Quit();
}
