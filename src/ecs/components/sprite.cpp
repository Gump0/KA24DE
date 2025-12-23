///////////////////////////////////////////////////////////////////
// component that handles rendering an image over an entity object
///////////////////////////////////////////////////////////////////
#include "sprite.h"

void Sprite::ComponentDebug(int objectId)
{
    std::string id = std::to_string(objectId);
    std::cout << id << " has a Sprite component!! :DD";
}
