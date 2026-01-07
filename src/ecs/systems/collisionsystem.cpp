#include "collisionsystem.hpp"
#include "../../KA24DE.hpp"

void CollisionSystem::Update()
{
    if(mEntities.size() <= 1)
        return;
    // Not ideal implementation since this collision system does use a O(N^2) solution.
    // Likely should change this at some point. For now it's here to show off system emplementation
    for(auto it1 = mEntities.begin(); it1 != mEntities.end(); it1++)
    {
        auto const& entity1 = *it1;

        auto& transform1 = gDictator.GetComponent<Transform>(entity1);
        auto collider1 = gDictator.GetComponent<Collider2D>(entity1);

        auto it2 = it1;
        ++it2;

        // calculate aabb bounds for entity1
        float left1 = transform1.PosX - (collider1.sizeX / 2);
        float right1 = transform1.PosX + (collider1.sizeX / 2);
        float bottom1 = transform1.PosY + (collider1.sizeY / 2);
        float top1 = transform1.PosY - (collider1.sizeY / 2);

        // if(it1 == mEntities.begin())
        // {
        //     SDL_Log("First Entity :: POSX: %f, POSY: %f", transform1.PosX, transform1.PosY);
        //     SDL_Log("  Bounds :: L:%f R:%f B:%f T:%f", left1, right1, bottom1, top1);
        // }
        // if(it1 == std::next(mEntities.begin()))
        // {
        //     SDL_Log("Second Entity :: POSX: %f, POSY: %f", transform1.PosX, transform1.PosY);
        //     SDL_Log("  Bounds :: L:%f R:%f B:%f T:%f", left1, right1, bottom1, top1);
        // }

        for(; it2 != mEntities.end(); ++it2)
        {
            auto const& entity2 = *it2;

            auto& transform2 = gDictator.GetComponent<Transform>(entity2);
            auto& collider2 = gDictator.GetComponent<Collider2D>(entity2);

            // TODO : add layer check
            // if(collider1.layer == collider2.layer)
            //     continue;

            // aabb bounds again
            float left2 = transform2.PosX - (collider2.sizeX / 2.0f);
            float right2 = transform2.PosX + (collider2.sizeX / 2.0f);
            float bottom2 = transform2.PosY + (collider2.sizeY / 2.0f);
            float top2 = transform2.PosY - (collider2.sizeY / 2.0f);

            // collision check
            if(left1 < right2 &&
                right1 > left2 &&
                top1 < bottom2 &&
                bottom1 > top2)
            {
                SDL_Log("THERES A COLLISION");
            }
        }
    }
}
