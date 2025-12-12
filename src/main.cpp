#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <cstdlib>
#include <string>
#include <system_error>

/* class prototypes */
/* "Lazy Texture Class" */
class LTexture
{
public:
    // init texture variables (constructor)
    LTexture();

    // clean-up texture variables (deconstructor)
    ~LTexture();

    // load texture from disk
    bool loadFromFile(std::string path);

    // clean-up texture
    void destroy();

    // draw texture
    void render(float x, float y);

    // get texture attributes
    int getWidth();
    int getHeight();
    bool isLoaded();

private:
    // contains texture data
    SDL_Texture* mTexture;

    // texture dimensions
    int mWidth;
    int mHeight;
};

constexpr int ScreenWidth { 1200 };
constexpr int ScreenHeight { 800 };

/* Global variables */
SDL_Window* gWindow { nullptr };
SDL_Surface* gScreenSurface { nullptr };
SDL_Surface* gHelloWorld { nullptr };
SDL_Renderer* gRenderer { nullptr };

// image we will render
LTexture gPngTexture;

// Start SDL and create a window.
bool init();
// loads media
bool loadMedia();
// frees media and shuts down SDL
void shutdown();

/* Class Implementations */
LTexture::LTexture():
    // init variables
    mTexture{ nullptr },
    mWidth{ 0 },
    mHeight{ 0 }
{

}

LTexture::~LTexture()
{
    destroy();
}

bool LTexture::loadFromFile(std::string path)
{
    destroy();

    // load surface
    if(SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr)
    {
        SDL_Log( "Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Create texture from surface
        if( mTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface ); mTexture == nullptr )
        {
            SDL_Log( "Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Clean up loaded surface
        SDL_DestroySurface( loadedSurface );
    }
    return mTexture != nullptr;
}

void LTexture::destroy()
{
    // clean-up texture
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

void LTexture::render(float x, float y)
{
    // set texture pos
    SDL_FRect dstRect{ x, y, static_cast<float>(mWidth), static_cast<float>(mHeight)};
    // render texture
    SDL_RenderTexture(gRenderer, mTexture, nullptr, &dstRect);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool LTexture::isLoaded()
{
    return mTexture != nullptr;
}

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
        if( SDL_CreateWindowAndRenderer( "SDL3 Tutorial: Textures and Extension Libraries", ScreenWidth, ScreenHeight, 0, &gWindow, &gRenderer ) == false )
        {
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
    //File loading flag
    bool success{ true };

    //Load splash image
    if( gPngTexture.loadFromFile(assetPath() + "loaded.png") == false )
    {
        SDL_Log( "Unable to load png image!\n");
        success = false;
    }

    return success;
}

void shutDown()
{
    //Clean up texture
    gPngTexture.destroy();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    gRenderer = nullptr;
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Final exit code
    int exitCode{ 0 };

    //Initialize
    if( init() == false )
    {
        SDL_Log( "Unable to initialize program!\n" );
        exitCode = 1;
    }
    else
    {
        //Load media
        if( loadMedia() == false )
        {
            SDL_Log( "Unable to load media!\n" );
            exitCode = 2;
        }
        else
        {
            //The quit flag
            bool quit{ false };

            //The event data
            SDL_Event e;
            SDL_zero( e );

            //The main loop
            while( quit == false )
            {
                //Get event data
                while( SDL_PollEvent( &e ) == true )
                {
                    //If event is quit type
                    if( e.type == SDL_EVENT_QUIT )
                    {
                        //End the main loop
                        quit = true;
                    }
                }

                // fill the background white
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                // render image on screen
                gPngTexture.render( 0.f, 0.f );

                // update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }

    // clean up
    shutDown();

    return exitCode;
}
