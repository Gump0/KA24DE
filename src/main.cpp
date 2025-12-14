/////////////////////////////////////
// the "entry point" to the program.
/////////////////////////////////////
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <string>

/* GLOBAL */
constexpr int gScreenWidth {1280};
constexpr int gScreenHeight {720};

SDL_Window* gWindow {nullptr};
SDL_Renderer* gRenderer {nullptr};

bool init()
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

bool render()
{
    // render logic ^^
    bool success {true};

    return success;
}

void shutDown()
{
    // cleanup program.
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_Quit();
}

int main(int argc, char* args[])
{
    int exitCode {0};
    if(!init())
    {
        SDL_Log("Unable to initialize program \n");
        exitCode = 1;
        return exitCode;
    }

    if(!render())
    {
        SDL_Log("Renderer failed to initalize \n");
        exitCode = 2;
        return exitCode;
    }
    else
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

    shutDown();
    return exitCode;
}
