/////////////////////////////////////////////////////////////
// definitions for each type used throughout the ecs system.
// (Entities, Components and System Signatures)
/////////////////////////////////////////////////////////////
#ifndef ENTITY_TYPE_H
#define ENTITY_TYPE_H

#include <bitset>
#include <cstdint>
//---------------------------------------------------------------------------------

//Entity relate data/limitations
using Entity = std::uint32_t;                   // stores entity id through entity type
const Entity MAX_ENTITIES = 5000;              // entity cap in-game

using ComponentType = std::uint8_t;             // component type represented as a 8bit int
const ComponentType MAX_COMPONENTS = 32;        // component cap on each entity

using Signature = std::bitset<MAX_COMPONENTS>;  // used as a method to check what item has what component.

#endif
