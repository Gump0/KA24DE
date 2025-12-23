///////////////////////////////////////////////////////
// handles basic location-based data
// e.g(world position, local rotation and local scale)
///////////////////////////////////////////////////////
#include "transform.h"
#include <string>

void Transform::ComponentDebug(int objectId)
{
    std::string id = std::to_string(objectId);
    std::cout << id << " has a Transform component!! :DD";
}
