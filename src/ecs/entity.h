#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <memory>
#include <vector>
#include "component.h"
//---------------------------------------------------------------------------------
class Entity
{
public:
    Entity(int id, std::string name = "");
    ~Entity();
    Entity(const Entity& obj);

private:
    int mId;
    std::string mName;
};

#endif
