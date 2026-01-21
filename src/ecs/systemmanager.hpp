///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// System Manager is in charge of maintaining a record of registered systems and their signatures.
// Whenever the user wants to implement their custom system they need to call the system manager to register said system.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "system.hpp"
#include "entitytype.hpp"
#include <unordered_map>
#include <memory>
#include <cassert>
//---------------------------------------------------------------------------------
class SystemManager
{
public:
    SystemManager() = default;
    SystemManager(const SystemManager&) = delete;
    SystemManager& operator=(const SystemManager&) = delete;

    template<typename T>
    T& GetSystem()
    {
        const char* typeName = typeid(T).name();

        auto it = mSystems.find(typeName);
        assert(it != mSystems.end() && "System not registered!");

        return *static_cast<T*>(it->second.get());
    }

    template<typename T>
    T& RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        assert(mSystems.find(typeName) == mSystems.end() && "ERROR : the same system cannot be registered more than once");

        auto system = std::make_unique<T>();
        T& ref = *system;

        mSystems.emplace(typeName, std::move(system));
        return ref;
    }

    template <typename T>
    void SetSignature(Signature signature)
    {
        const char* typeName = typeid(T).name();

        assert(mSignatures.find(typeName) == mSignatures.end() && "ERROR : an access attempt has been made to a system that is not registered yet");

        // set signature for the system
        mSignatures.insert({typeName, signature});
    }

    void EntityDestroyed(Entity entity)
    {
        // erase a destroyed entity from system list
        // so that that entity is not iterated over (we don't like wasting cpu cache)
        for(auto const& pair : mSystems)
        {
            auto const& system = pair.second;

            system->mEntities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature signature)
    {
        // let each system know when a entities signature changes
        for(auto const& pair : mSystems)
        {
           auto const& type = pair.first;
           auto const& system = pair.second;
           auto const& systemSignature = mSignatures[type];

           if((signature & systemSignature) == systemSignature)
           {
               // insert if entity signature matches
               system->mEntities.insert(entity);
           }
           else
           {
               // erase if not.
               system->mEntities.erase(entity);
           }
        }
    }

private:
    // hashmap from system type string pointer => signature
	std::unordered_map<const char*, Signature> mSignatures{};

	// hashmap from system type string pointer => system pointer
	std::unordered_map<const char*, std::unique_ptr<System>> mSystems{};
};

#endif
