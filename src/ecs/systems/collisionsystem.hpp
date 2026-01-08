///////////////////////////////////////////////////////
// handles checking for collisions on entity objects.
// requires (transform, collider2d)
///////////////////////////////////////////////////////
#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "../system.hpp"
#include "../components/collider2d.hpp"
#include "../components/transform.hpp"
#include <vector>
//---------------------------------------------------------------------------------
class CollisionSystem : public System
{
    struct CollisionPair
    {
        Entity entity1;
        Entity entity2;
        // bool isTrigger;
    };
    std::vector<CollisionPair> mCurrentCollisions;  // current collisions

public:
    void Update();
    bool EntityIsColliding(Entity entity)
    {
        for(auto colPair : mCurrentCollisions)
        {
            if(colPair.entity1 == entity || colPair.entity2 == entity)
                return true;
        }
        return false;
    };
};

#endif
