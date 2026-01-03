#include "playermove.hpp"
#include "../components/transform.hpp"
#include "../../KA24DE.hpp"
#include "../../input-manager/input.hpp"

void PlayerMove::Update(double deltaTime)
{
    for(auto& entity : mEntities)
    {
        auto& transform = gDictator.GetComponent<Transform>(entity);

        mYVelocity = (Input::GetKey(KeyCode::S) - Input::GetKey(KeyCode::W)) * MOVE_SPEED;
        mXVelocity = (Input::GetKey(KeyCode::D) - Input::GetKey(KeyCode::A)) * MOVE_SPEED;

        transform.PosX += mXVelocity * deltaTime;
        transform.PosY += mYVelocity * deltaTime;
    }
}
