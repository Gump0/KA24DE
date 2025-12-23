#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../component.h"
//---------------------------------------------------------------------------------
class Transform : public Component
{
public:
    // 2 dimensional transform data
    struct Position
    {
        float x;
        float y;
    };

    struct Rotation
    {
        float x;
        float y;
    };

    struct Scale
    {
        float x;
        float y;
    };
};
#endif
