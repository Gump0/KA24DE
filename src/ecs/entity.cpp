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

Entity::Entity(std::string name)
{
    // generate id
    mId = rand() % 32767;
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
