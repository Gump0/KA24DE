////////////////////////////////////////////////////////////////////
// player controller re-write using user-script abstraction
// EXAMPLE OF HOW USER SCRIPTS WOULD BE WRITTEN TO INTERFACE ENGINE
////////////////////////////////////////////////////////////////////
#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "../KA24DE.hpp"
#include "../ecs/components/playerbody.hpp"
#include "../ecs/components/transform.hpp"
//---------------------------------------------------------------------------------

class PlayerController : public Script
{
public:
    void Start(Dictator& dictator, Entity entity) override
    {
        auto& transform = dictator.GetComponent<Transform>(entity);
        transform.PosX = 100;
        transform.PosY = 100;

        mEntity = entity;
    }

    void Update(Dictator& dictator, Entity entity, double deltaTime) override
    {
        auto& transform = dictator.GetComponent<Transform>(entity);
        auto& playerbody = gDictator.GetComponent<Playerbody>(entity);

        mYVelocity = (Input::GetKey(KeyCode::S) - Input::GetKey(KeyCode::W)) * playerbody.MOVE_SPEED;
        mXVelocity = (Input::GetKey(KeyCode::D) - Input::GetKey(KeyCode::A)) * playerbody.MOVE_SPEED;

        transform.PosX += mXVelocity * deltaTime;
        transform.PosY += mYVelocity * deltaTime;
    }

    void OnDestroy(Dictator& dictator, Entity entity) override
    {
        SDL_Log("Player destroyed!");
    }

private:
    Entity mEntity;
    float mXVelocity {0}, mYVelocity {0};
};

#endif
