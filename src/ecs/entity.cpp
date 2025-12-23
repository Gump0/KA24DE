////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// handles logic for individual entities within the game-world
// think of "GameObjects" from Unity or a similar entity system you would see in a trillion other game engines
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "entity.h"

void Entity::Update()
{
    // update each component
    for(auto& component : mComponents)
    {
        component->Update();
    }
}

Entity::Entity(int id, std::string name)
{
    // assign id (entity system  will keep track of entity ids)
    mId = id;
    if(name.empty())
    {
        std::string newName = std::to_string(mId);
        this->mName = newName;
    }
    else
    {
        this->mName = name;
    }

}

Entity::~Entity() {}
