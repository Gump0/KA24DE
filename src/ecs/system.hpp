/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A system is any functionality that iterates upon a list of entities with a certain signature of components
// lets say if I want my phyiscs body component to have gravity applied, a gravity system must be made that
// inherits from this system base-class.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SYSTEM_H
#define SYSTEM_H

#include "entitytype.hpp"
#include <set>
//---------------------------------------------------------------------------------
class System
{
public:
    std::set<Entity> mEntities;
};

#endif
