//////////////////////////////////////////////////////////////////////////////////
// The entity manager is in charge of distrubuting entity id's and keeping track
// of which ones are in-use and which ones are not.
//////////////////////////////////////////////////////////////////////////////////
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entitytype.hpp"
#include <SDL3/SDL_gpu.h>
#include <queue>
#include <array>
#include <cassert>
//---------------------------------------------------------------------------------
class EntityManger
{
public:
    EntityManger()
    {
        // initialize the queue with EVERY possible id
        for(Entity entity{0}; entity < MAX_ENTITIES; entity++)
        {
            mVacantEntites.push(entity);
        }
    }

    ~EntityManger() = default;
    EntityManger(const EntityManger& obj) = default;

    Entity CreateEntity()
    {
        assert(mActiveEntities < MAX_ENTITIES && "ERROR : too many entites in existance");

        Entity id = mVacantEntites.front();
        mVacantEntites.pop();
        ++mActiveEntities;

        return id;
    }

    void DeleteEntity(Entity entity)
    {
        assert(entity < MAX_COMPONENTS && "ERROR : entity is out of range");

        // wipe the entities current signature
        mSignatures[entity].reset();
        // put the destroyed id to the back of the queue
        mVacantEntites.push(entity);
        --mActiveEntities;
    }

    void SetSignature(Entity entity, Signature signature)
    {
        assert(entity < MAX_COMPONENTS && "ERROR : entity is out of range");

        mSignatures[entity] = signature;
    }

    Signature GetSignature(Entity entity)
    {
        assert(entity < MAX_COMPONENTS && "ERROR : entity is out of range");

        return mSignatures[entity];
    }

private:
    // queue of unused entity id's
    std::queue<Entity> mVacantEntites {};

    // array that contains signatures where each where the index corresponds to the entity id
    std::array<Signature, MAX_ENTITIES> mSignatures {};

    // keep track of current number of instantiated entities
    uint32_t mActiveEntities {0};
};

#endif
