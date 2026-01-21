#include "KA24DE.hpp"
#include <memory>

// ecs components
#include "ecs/components/collider2d.hpp"
#include "ecs/components/physicsbody.hpp"
#include "ecs/components/playerbody.hpp"
#include "ecs/components/spriterenderer.hpp"
#include "ecs/components/transform.hpp"

// ecs built-in systems
#include "ecs/systems/collisionsystem.hpp"
#include "ecs/systems/spriterenderingsystem.hpp"
#include "ecs/systems/scriptinglayer.hpp"

// ecs user-made "script" systems
#include "user-scripts/playercontroller.hpp"
#include "user-scripts/switchspritetest.hpp"

Dictator gDictator;

KA24DE::KA24DE()
{
    // register component types we will use for our "game"
    gDictator.RegisterComponent<Transform>();
    gDictator.RegisterComponent<SpriteRenderer>();
    gDictator.RegisterComponent<Collider2D>();
    gDictator.RegisterComponent<Playerbody>();
    gDictator.RegisterComponent<PhysicsBody>();

    // register system under system manager
    // sprite rendering system
    spriteRenderingSystem = &gDictator.RegisterSystem<SpriteRenderingSystem>();
    {
        Signature sig;
        sig.set(gDictator.GetComponentType<Transform>());
        sig.set(gDictator.GetComponentType<SpriteRenderer>());
        gDictator.SetSystemSignature<SpriteRenderingSystem>(sig);
    }
    spriteRenderingSystem->Init();

    // collision system
    // collisionSystem = &gDictator.RegisterSystem<CollisionSystem>();
    collisionSystem = &gDictator.RegisterSystem<CollisionSystem>();
    {
        Signature sig;
        sig.set(gDictator.GetComponentType<Transform>());
        sig.set(gDictator.GetComponentType<Collider2D>());
        gDictator.SetSystemSignature<CollisionSystem>(sig);
    }

    // user scripting layer system
    scriptingLayer = &gDictator.RegisterSystem<ScriptingLayer>();
    scriptingLayer->Init(&gDictator);

    // physics system
    // tbd..

    // SPAWN ENTITY 1 TEST
    auto entity1 = gDictator.CreateEntity();
    gDictator.AddComponent(entity1, SpriteRenderer {
            nullptr,
            "cat0.bmp",
            50,
            50,
            false,
        }
    );
    gDictator.AddComponent(entity1, Transform {
            640.0f,
            350.0f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
        }
    );
    gDictator.AddComponent(entity1, Collider2D {
            50,
            50,
        }
    );
    gDictator.AddComponent(entity1, Playerbody {
            500.0f,
        }
    );

    // player move system (work with scriping layer)
    scriptingLayer->AddScript<PlayerController>(entity1);

    // SPAWN ENTITY TWO TEST
    auto entity2 = gDictator.CreateEntity();
    gDictator.AddComponent(entity2, Transform {
            530.0f,
            350.0f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
        });
    gDictator.AddComponent(entity2, SpriteRenderer {
            nullptr,
            "green-ball.bmp",
            50,
            50,
            false,
        });
        gDictator.AddComponent(entity2, Collider2D {
            50,
            50
        });

    scriptingLayer->AddScript<SwitchSpriteTest>(entity2);

    // SPAWN ENTITY THREE TEST
    auto entity3 = gDictator.CreateEntity();
    gDictator.AddComponent(entity3, Transform {
            630.0f,
            460.0f,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
        });
    gDictator.AddComponent(entity3, SpriteRenderer {
            nullptr,
            "green-ball.bmp",
            50,
            50,
            false,
        });
        gDictator.AddComponent(entity3, Collider2D {
            50,
            50
        });

    scriptingLayer->AddScript<SwitchSpriteTest>(entity3);
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

    return success;
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
        SDL_SetRenderDrawColor(mRenderer, 81, 79, 132, 255);    // background
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

        // scripting layer
        scriptingLayer->Update(deltaTime);

        // test area :P
        if(Input::GetMouseButtonDown(MouseCode::LEFTMOUSE))
        {
            SDL_Log("%f", deltaTime);
        }
    }
}
