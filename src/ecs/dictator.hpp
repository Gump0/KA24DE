///////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Dictator class. every good leader needs have authority.
// the user will interface with this class whenever they wish to access the
// System manager, Entity Manager, and Componenet Manager (and kinda component containers)
// Think of this class as the middle-man for the user whenever they wish to interact with the ecs system.
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef DICTATOR_H
#define DICTATOR_H

#include "components/script.hpp"
#include "systemmanager.hpp"
#include "entitymanager.hpp"
#include "componentmanager.hpp"
#include "entitytype.hpp"
#include "systems/collisionsystem.hpp"
#include "systems/scriptinglayer.hpp"
#include "systems/spriterenderingsystem.hpp"
#include <cassert>
#include <memory>
#include <utility>
//---------------------------------------------------------------------------------
class Dictator
{
public:
    Dictator() = default;
    Dictator(const Dictator&) = delete;
    Dictator& operator=(const Dictator&) = delete;

    // core system
    void Register(std::unique_ptr<SpriteRenderingSystem> s)
    {
        spriteRenderingSystem = std::move(s);
    }

    void Register(std::unique_ptr<CollisionSystem> c)
    {
        collisionSystem = std::move(c);
    }

    void Register(std::unique_ptr<ScriptingLayer> s)
    {
        scriptingLayer = std::move(s);
    }

    template<typename T>
    T& GetCore();

    void Init()
    {
        mComponentManager = std::make_unique<ComponentManager>();
        mSystemManager = std::make_unique<SystemManager>();
        mEntityManager = std::make_unique<EntityManger>();
    }

    // entity manager
    Entity CreateEntity()
    {
        return mEntityManager->CreateEntity();
    }

    void DeleteEntity(Entity entity)
    {
        mEntityManager->DeleteEntity(entity);
        mComponentManager->EntityDeleted(entity);
        mSystemManager->EntityDestroyed(entity);
    }

    uint32_t ActiveEntities()
    {
        return mEntityManager->ActiveEntities();
    }

    // component manager
    template<typename T>
    void RegisterComponent()
    {
        mComponentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component)
    {
        mComponentManager->AddComponent<T>(entity, component);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
    }

   	template<typename T>
	void RemoveComponent(Entity entity)
	{
		mComponentManager->RemoveComponent<T>(entity);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return mComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return mComponentManager->GetComponentType<T>();
	}

	// system manager
	template<typename T>
	T& RegisterSystem()
	{
		return mSystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		mSystemManager->SetSignature<T>(signature);
	}

private:
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<SystemManager> mSystemManager;
    std::unique_ptr<EntityManger> mEntityManager;

    std::unique_ptr<SpriteRenderingSystem> spriteRenderingSystem;
    std::unique_ptr<CollisionSystem> collisionSystem;
    std::unique_ptr<ScriptingLayer> scriptingLayer;
};

template<>
inline CollisionSystem& Dictator::GetCore<CollisionSystem>()
{
    assert(collisionSystem);
    return *collisionSystem;
}

template<>
inline SpriteRenderingSystem& Dictator::GetCore<SpriteRenderingSystem>()
{
    assert(spriteRenderingSystem);
    return *spriteRenderingSystem;
}

template<>
inline ScriptingLayer& Dictator::GetCore<ScriptingLayer>()
{
    assert(scriptingLayer);
    return *scriptingLayer;
}

#endif
