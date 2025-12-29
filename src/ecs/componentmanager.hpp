///////////////////////////////////////////////////////////////////////////////////////
// ahh yes the Component Manager.
// This class is in charge of managing each component container when a component NEEDS
// to be added or removed.
///////////////////////////////////////////////////////////////////////////////////////
#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "componentcontainer.hpp"
#include "entitytype.hpp"
#include <unordered_map>
#include <memory>
//---------------------------------------------------------------------------------
class ComponentManager
{
public:
    ComponentManager() = default;
    ~ComponentManager() = default;
    ComponentManager(const ComponentManager &obj);

    template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");

		mComponentTypes.insert({typeName, mNextComponentType});
		mComponentContainers.insert({typeName, std::make_shared<ComponentContainer<T>>()});
		++mNextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

		return mComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		GetComponentContainer<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentContainer<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return GetComponentContainer<T>()->GetComponent(entity);
	}

	void EntityDeleted(Entity entity)
	{
		for (auto const& pair : mComponentContainers)
		{
			auto const& component = pair.second;

			component->EntityDeleted(entity);
		}
	}


private:
    // map from string pointer => component type
    std::unordered_map<const char*, ComponentType> mComponentTypes {};

    // map from string pointer => component container
    std::unordered_map<const char*, std::shared_ptr<IComponentContainer>> mComponentContainers {};

    // The component type to be assigned to the next registered component - starting at 0
	ComponentType mNextComponentType{};

	// helper method to get a statically casted pointer to Component Container of type T
	template<typename T>
	std::shared_ptr<ComponentContainer<T>> GetComponentContainer()
	{
	    const char* typeName = typeid(T).name();
		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");
		return std::static_pointer_cast<ComponentContainer<T>>(mComponentContainers[typeName]);
	}
};

#endif
