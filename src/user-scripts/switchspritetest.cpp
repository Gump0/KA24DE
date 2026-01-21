#include "switchspritetest.hpp"
#include <iostream>

void SwitchSpriteTest::Update(Dictator& dictator, Entity entity, double deltaTime)
{
    auto& collisionSystem = dictator.GetSystem<CollisionSystem>();

    if(collisionSystem.EntityIsColliding(entity))
    {
        auto& sr = dictator.GetComponent<SpriteRenderer>(entity);
        std::string desiredSprite = "red-ball.bmp";
        if(sr.imgLocation != desiredSprite)
        {
            sr.imgLocation = desiredSprite;
            sr.isLoaded = false;    // tell sprite rendering system to re-load sprite
        }
    }
    else
    {
        auto& sr = dictator.GetComponent<SpriteRenderer>(entity);

        std::string desiredSprite = "green-ball.bmp";
        if(sr.imgLocation != desiredSprite)
        {
            sr.imgLocation = desiredSprite;
            sr.isLoaded = false;
        }
    }
}
