#include "pch.h"
#include "Enemy.h"
#include "Renderer.h"
#include "Engine.h"
#include "Player.h"

void Enemy::Update(float dt) {

    Player* player = m_scene-> GetActorByName<Player>("Player");
    if (player) {
        nu::Vector2 direction = (player->GetTransform().position - m_transform.position).Normalized();
        float rotation = direction.Angle();
        SetRotation(rotation * nu::RadtoDeg);

        nu::Vector2 forward{ 1, 0 };
        forward = forward.Rotate(m_transform.rotation * nu::DegtoRad);
        AddVelocity(forward * m_speed * dt);
    }

    float thrust = 0.0f;

    float rotate = 0.0f;
    
    /*nu::Vector2 forward{ 1,0 };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegtoRad) * thrust;*/
    //AddVelocity(velocity * dt);

    //SetVelocity(GetVelocity() + (force * dt));

    Actor::Update(dt);

}

void Enemy::Draw(const nu::Renderer& renderer) const {
    Actor::Draw(renderer);
}
