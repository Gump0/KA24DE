////////////////////////////////////////////////////////////////////////////////////////////////
// stores and manages active components in-game
// a data structure that's pretty much just a glorified array
// the thing is about ecs is that theres no point of using it if your not actually
// taking advantage of it's benefits. so we need to make sure that all data is "packed tight"
// heavy inspiration from austin morlan's solution since im still a newb
// (austinmorlan.com/posts/entity_component_system)
////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef COMPONENT_CONTAINER_H
#define COMPONENT_CONTAINER_H

#include "entitytype.hpp"
#include <array>
#include <cassert>
#include <unordered_map>
//---------------------------------------------------------------------------------
class IComponentContainer
{
public:
    ~IComponentContainer();
    virtual void EntityDeleted(Entity entity) = 0;
};

template<typename T>
class ComponentContainer : public IComponentContainer
{
public:
    void AddComponent(Entity entity, T component)
    {
        assert(mEntityToIndex.find(entity) == mEntityToIndex.end() && "ERROR : component added to same entity more than once.");

        // add new entry at the end fo the container
        size_t newIndex = mSize;
        mEntityToIndex[entity] = newIndex;
        mIndexToEntity[newIndex] = entity;
        mComponentArray[newIndex] = component;
        mSize++;
    }

    void RemoveComponent(Entity entity, T component)
    {
        assert(mEntityToIndex.find(entity) != mEntityToIndex.end() && "ERROR : removing non-existent component");

        // copy element at end to deleted elements place to maintain density
        size_t removedEntityIndex = mEntityToIndex[entity];
        size_t endIndex = mSize - 1;
        mComponentArray[removedEntityIndex] = mComponentArray[endIndex];

        // update hashmap to point to moved spot
        Entity entityOfLastElement = mIndexToEntity[removedEntityIndex];
        mEntityToIndex[entityOfLastElement] = mIndexToEntity[endIndex];
        mIndexToEntity[endIndex] = entityOfLastElement;

        mEntityToIndex.erase(entity);
        mIndexToEntity.erase(endIndex);
        mSize--;
    }

    T& GetComponent(Entity entity)
    {
        assert(mEntityToIndex.find(entity) != mEntityToIndex.end() && "ERROR : retrieving non-existent component");

        size_t entityIndex = mEntityToIndex[entity];
        return mComponentArray[entityIndex];
    }

    void EntityDeleted(Entity entity) override
    {
        if(mEntityToIndex.find(entity) != mEntityToIndex.end())
        {
            RemoveComponent(entity);
        }
    }

private:
    // The packed array of components of generic type T
    // set to capacity of MAX_ENTITIES so that everyone has a spot :)
    std::array<T, MAX_ENTITIES> mComponentArray {};

    // map to convert entity id to component index
    std::unordered_map<Entity, size_t> mEntityToIndex {};

    // map to convert componrnt index to entity id
    std::unordered_map<Entity, size_t> mIndexToEntity {};

    // total size of valid entries in array
    size_t mSize;
};

#endif
