#include "switchspritetest.hpp"

void SwitchSpriteTest::Update(Dictator& dictator, Entity entity, double deltaTime)
{
    auto& collisionSystem = dictator.GetSystem<CollisionSystem>();

    if(collisionSystem.EntityIsColliding(entity))
    {
        SDL_Log("WE MADE IT");
    }
}
