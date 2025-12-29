////////////////////////////////////////////////////////
// handles updating phyiscs on physics-bodied entities
// (requires transform, physics body)
////////////////////////////////////////////////////////
#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "../system.hpp"
//---------------------------------------------------------------------------------
class PhysicsSystem : public System
{
public:
    void Update(double deltaTime);
};

#endif
