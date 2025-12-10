#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <cstdlib>
#include <string>

constexpr int ScreenWidth { 1200 };
constexpr int ScreenHeight { 800 };

SDL_Window* gWindow { nullptr };
SDL_Surface* gScreenSurface { nullptr };
SDL_Surface* gHelloWorld { nullptr };

// Start SDL and create a window.
bool init();
// loads media
bool loadMedia();
// frees media and shuts down SDL
void shutdown();

std::string assetPath()
{
    // e.g. "path/to/project/build/bin/"
    std::string base(SDL_GetBasePath());

    // Move UP one folder to get "build/"
    // and then assume assets are in ProjectRoot/assets/
    return base + "../assets/";
}

bool init()
{
    // init flag
    bool success{ true };

    // init SDL
    if( SDL_Init( SDL_INIT_VIDEO ) == false ) {
        SDL_Log( "SDL could not initialize! SDL error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        // create window
        if( gWindow = SDL_CreateWindow( "SDL3 Tutorial: Hello SDL3", ScreenWidth, ScreenHeight, 0 ); gWindow == nullptr ) {
            SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            // get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia()
{
    bool success { true };

    // load splash image
    std::string imagePath { assetPath() + "hello-sdl3.bmp" };
    if(gHelloWorld = SDL_LoadBMP(imagePath.c_str()); gHelloWorld == nullptr) {
        SDL_Log("Unable to load image %s! SDL ERROR %s\n", imagePath.c_str(), SDL_GetError());
        success = false;
    }

    return success;
}

void shutDown()
{
    // clean-up surface
    SDL_DestroySurface(gHelloWorld);
    gHelloWorld = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gScreenSurface = nullptr;

    SDL_Quit();
}

int main(int argc, char* args[])
{
    // final exit code
    int exitCode = { 0 };

    // initialize
    if(init() == false) {
        SDL_Log("Unable to Init program!!\n");
        exitCode = 1;
    }
    else {
        // attempt to load media
        if(loadMedia() == false) {
            SDL_Log("Unable to load media!\n");
            exitCode = 2;
        }
        else {
            // quit flag
            bool quit { false };

            // event data
            SDL_Event e;
            SDL_zero(e);

            // main "game-loop"
            while(quit == false) {
                // get event data
                while(SDL_PollEvent(&e) == true) {
                    // if it's a quit type
                    if(e.type == SDL_EVENT_QUIT) {
                        // end the main loop
                        quit = true;
                    }
                }

                // fill surface white
                SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));

                // render image to screen
                SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

                // update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    shutDown();
    return exitCode;
}
