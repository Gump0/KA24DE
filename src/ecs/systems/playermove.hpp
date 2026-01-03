/////////////////////////////////////////////////////
// system that handles simple WASD player movement.
// requires (transform)
/////////////////////////////////////////////////////
#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H

#include "../system.hpp"
//---------------------------------------------------------------------------------a
class PlayerMove : public System
{
public:
    void Update(double deltaTime);
private:
    const float MOVE_SPEED {100.0f};
    float mXVelocity {0}, mYVelocity {0};
};

#endif
