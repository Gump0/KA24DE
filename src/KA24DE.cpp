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
    if(mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }

    if(mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    SDL_Quit();
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
        mScreenWidth, mScreenHeight, SDL_WINDOW_MAXIMIZED,
        &mWindow, &mRenderer ))
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

        SDL_SetRenderDrawColor(mRenderer, 230, 115, 0, 255);
        SDL_RenderClear(mRenderer);
        SDL_RenderPresent(mRenderer);
    }
}
