#include "switchspritetest.hpp"
#include "../ecs/components/transform.hpp"
#include "../ecs/components/collider2d.hpp"
#include "../ecs/components/spriterenderer.hpp"
#include <iostream>

void SwitchSpriteTest::Update(Dictator& dictator, Entity entity, double deltaTime)
{
    auto& transform = dictator.GetComponent<Transform>(entity);
    auto& collider = dictator.GetComponent<Collider2D>(entity);
    auto& sr = dictator.GetComponent<SpriteRenderer>(entity);

    auto& collisionsystem = dictator.GetCore<CollisionSystem>();
    SDL_Log("User Script's Dictator System : %p", (void*)&dictator);
    std::cout << std::to_string(entity) << '\n';

    if(collisionsystem.EntityIsColliding(entity))
    {
        SDL_Log("WE MADE IT");
    }
}
