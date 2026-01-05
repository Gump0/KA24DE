/////////////////////////////////////////////////////
// system that handles simple WASD player movement.
// requires (transform)
/////////////////////////////////////////////////////
#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H

#include "../system.hpp"
//---------------------------------------------------------------------------------
class PlayerMove : public System
{
public:
    void Update(double deltaTime);
private:
    float mXVelocity {0}, mYVelocity {0};
};

#endif
