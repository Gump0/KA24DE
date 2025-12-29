#include "physicssystem.hpp"
#include "../components/physicsbody.hpp"
#include "../components/transform.hpp"
#include "../../KA24DE.hpp"

void PhysicsSystem::Update(double deltaTime)
{
    for(auto const& entity : mEntities)
    {
        // get required component refrences.
        auto& rigidBody = gDictator.GetComponent<PhysicsBody>(entity);
        auto& transform = gDictator.GetComponent<Transform>(entity);

        // gravity code here.
    }
}
