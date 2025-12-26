#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <unordered_map>
#include "entity.h"
#include "component.h" // all component && subcomponents..
#include "components/transform.h"
#include "components/sprite.h"
#include "components/physicsbody.h"
//---------------------------------------------------------------------------------
class EntityManger
{
public:
    EntityManger();
    ~EntityManger();

    Entity FindEntity(int objectId);    // returns entity by id (returns nullptr if non is found)
    void DeleteEntity(int objectId);    // deletes entity by id

    template <typename... Components>   // template method to create new entities
    Entity& NewEntity(std::string name, Components&&... components)
    {
        int entityId = mNextEntityValue;
        Entity* newEntity = new Entity(entityId);
        mEntityMap[entityId] = newEntity;
        mNextEntityValue++;

        // this is apparently how you add each component using a fold expression (c++ 17+)
        (AddComponentInternal(entityId, std::forward<Components>(components)), ...);

        return *newEntity;
    };

    template<typename T>                // template method to insert component
    void AddComponent(int objectId, T&& component)
    {
        if(mEntityMap.find(objectId) == mEntityMap.end())
        {
            std::string errid = std::to_string(objectId);
            std::cout << "Entity within the scene does not exist with object id of " << errid << "\n";
            return;
        }
        static_assert(std::is_trivially_copyable_v<std::decay_t<T>>, "Components must be trivially copyable");
    };

private:
    std::unordered_map<int, Entity> mEntityMap = { };       // probably would need refactoring later but for now we will use a hashmap
    std::unordered_map<int, void*> mComponents = { };     // we store EACH component in a hashmap and "enable/disable" component behaviors

    template<typename T>
    void AddComponentInternal(int entityId, T&& component)
    {
        T* componentPtr = new T(std::forward<T>(component));
        mComponents[typeid(T)][entityId] = static_cast<void*>(componentPtr);
    }

    int mNextEntityValue { 0 };
};

#endif
