////////////////////////////////////////////////////////
// simple user script that changes sprites on-collision
////////////////////////////////////////////////////////
#ifndef SPRITE_SWITCH_H
#define SPRITE_SWITCH_H

#include "../ecs/systems/scriptinglayer.hpp"
#include "../KA24DE.hpp"
//---------------------------------------------------------------------------------
class SwitchSpriteTest : public Script
{
public:
    void Start(Dictator& dictator, Entity entity) override { }

    void Update(Dictator& dictator, Entity entity, double deltaTime) override;

    void OnDestroy(Dictator& dictator, Entity entity) override
    {
        SDL_Log("Player destroyed!");
    }
};

#endif
