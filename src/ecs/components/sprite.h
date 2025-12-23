#ifndef SPRITE_H
#define SPRITE_H

#include "../component.h"
//---------------------------------------------------------------------------------
class Sprite : public Component
{
public:
    std::string imageReference = "";
    void ComponentDebug(int objectId) override;
};
#endif
