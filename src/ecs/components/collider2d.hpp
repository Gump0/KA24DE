#ifndef COLLIDER_2D_H
#define COLLIDER_2D_H

#include <bitset>
//---------------------------------------------------------------------------------
struct Collider2D
{
    float sizeX;
    float sizeY;

    bool isTrigger {false};
    bool isStatic {false};

    std::bitset<4> layer;
    std::string tag {""};
};

#endif
