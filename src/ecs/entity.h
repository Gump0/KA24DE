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
    void Update();                                      // updates all components in mComponents
    void AddComponent(std::unique_ptr<Component>);      // when dev wants to add component to entity
    Entity(int id, std::string name = "");

private:
    ~Entity();

    int mId;
    std::string mName;
    std::pmr::vector<std::unique_ptr<Component>> mComponents;
};

#endif
