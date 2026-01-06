/////////////////////////////////////////////////////////////////////////////////////////////////////
// class file that will manage the construction of global variables, system classes and destruction.
/////////////////////////////////////////////////////////////////////////////////////////////////////
#include "KA24DE.hpp"
#include "ecs/components/collider2d.hpp"
#include "ecs/components/physicsbody.hpp"
#include "ecs/components/playerbody.hpp"
#include "ecs/components/spriterenderer.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/systems/collisionsystem.hpp"
#include "ecs/systems/spriterenderingsystem.hpp"
#include "ecs/systems/playermove.hpp"
// system stuff ^^
#include <memory> // redundant after fix

Dictator gDictator;

// TEMPERARY (WILL HAVE A MORE OFFICIAL WAY OF DOING THIS L8R)
std::shared_ptr<SpriteRenderingSystem> spriteRenderingSystem;
std::shared_ptr<CollisionSystem> collisionSystem;
std::shared_ptr<PlayerMove> playerMove;

KA24DE::KA24DE()
{
    gDictator.Init();
    // register component types we will use for our "game"
    gDictator.RegisterComponent<Transform>();
    gDictator.RegisterComponent<SpriteRenderer>();
    gDictator.RegisterComponent<Collider2D>();
    gDictator.RegisterComponent<Playerbody>();
    gDictator.RegisterComponent<PhysicsBody>();

    // register system under system manager
    // sprite rendering system
    spriteRenderingSystem = gDictator.RegisterSystem<SpriteRenderingSystem>();
    {
        Signature sig;
        sig.set(gDictator.GetComponentType<Transform>());
        sig.set(gDictator.GetComponentType<SpriteRenderer>());
        gDictator.SetSystemSignature<SpriteRenderingSystem>(sig);
    }
    spriteRenderingSystem->Init();

    // collision system
    collisionSystem = gDictator.RegisterSystem<CollisionSystem>();
    {
        Signature sig;
        sig.set(gDictator.GetComponentType<Transform>());
        sig.set(gDictator.GetComponentType<Collider2D>());
        gDictator.SetSystemSignature<CollisionSystem>(sig);
    }

    // physics system
    // tbd..

    // player move system
    playerMove = gDictator.RegisterSystem<PlayerMove>();
    {
        Signature sig;
        sig.set(gDictator.GetComponentType<Transform>());
        sig.set(gDictator.GetComponentType<Playerbody>());
        gDictator.SetSystemSignature<PlayerMove>(sig);
    }

    // SPAWN ENTITY 1 TEST
    auto entity1 = gDictator.CreateEntity();
    gDictator.AddComponent(entity1,
        SpriteRenderer {
            nullptr,
            "cat0.bmp",
            50,
            50,
            false,
        }
    );
    gDictator.AddComponent(entity1,
        Transform {
            640.0f,
            350.0f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
        }
    );
    gDictator.AddComponent(entity1,
        Collider2D {
            50,
            50,
        }
    );
    gDictator.AddComponent(entity1,
        Playerbody {
            500.0f,
        }
    );

    // SPAWN ENTITY TWO TEST
    auto entity2 = gDictator.CreateEntity();
    gDictator.AddComponent(entity2,
        Transform {
            530.0f,
            350.0f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
        });
    gDictator.AddComponent(entity2,
        SpriteRenderer {
            nullptr,
            "cat0.bmp",
            50,
            50,
            false,
        });
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
    // call start after initialization
    start();

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
        SDL_SetRenderDrawColor(mRenderer, 230, 115, 0, 255);    // background
        SDL_RenderClear(mRenderer);                             // clear screen
        spriteRenderingSystem->Render(mRenderer);               // render ghetto test implemntation
        SDL_RenderPresent(mRenderer);                           // place data from mRenderer on-screen

        // time calculations
        auto nowTime = engineClock::now();
        std::chrono::duration<double> delta = nowTime - lastTime;
        lastTime = nowTime;
        deltaTime = delta.count();

        // collision
        collisionSystem->Update();

        // player move
        playerMove->Update(deltaTime);

        // test area :P
        if(Input::GetMouseButtonDown(MouseCode::LEFTMOUSE))
        {
            SDL_Log("%f", deltaTime);
        }
    }
}
