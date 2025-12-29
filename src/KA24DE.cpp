/////////////////////////////////////////////////////////////////////////////////////////////////////
// class file that will manage the construction of global variables, system classes and destruction.
/////////////////////////////////////////////////////////////////////////////////////////////////////
#include "KA24DE.hpp"

Dictator gDictator;

KA24DE::KA24DE()
{
    gDictator.Init();
}

KA24DE::~KA24DE()
{
    // cleanup object references to game engine systems
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

    if(!SDL_CreateWindowAndRenderer( "KA24DE :: NO GAME NAME",
        mScreenWidth, mScreenHeight, SDL_WINDOW_MAXIMIZED,
        &mWindow, &mRenderer ))
    {
        SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
        success = false;
    }

    // init game engine systems

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

    auto lastTime = engineClock::now();

    while(quit == false)
    {
        Input::Update();
        while(SDL_PollEvent(&e) == true)
        {
            if(e.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
            Input::ProcessEvent(e);
        }
        // update loop
        // rendering
        SDL_SetRenderDrawColor(mRenderer, 230, 115, 0, 255);
        SDL_RenderClear(mRenderer);
        SDL_RenderPresent(mRenderer);

        // time calculations
        auto nowTime = engineClock::now();
        std::chrono::duration<double> delta = nowTime - lastTime;
        lastTime = nowTime;
        deltaTime = delta.count();

        // test area :P
        if(Input::GetMouseButtonDown(MouseCode::LEFTMOUSE))
        {
            SDL_Log("Kinna ghetto");
        }

        if(Input::GetKeyDown(KeyCode::W))
        {
            SDL_Log("%f", deltaTime);
        }
    }
}
