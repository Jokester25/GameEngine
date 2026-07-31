#include "pch.h"
#include "Enemy.h"
#include "Renderer.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"

void Enemy::Update(float dt) {
    float thrust = 0.0f;

    float rotate = 0.0f;

    Player* player = m_scene-> GetActorByName<Player>("Player");
    if (player) {
        nu::Vector2 direction = (player->GetTransform().position - m_transform.position).Normalized();
        float rotation = direction.Angle();
        SetRotation(rotation * nu::RadtoDeg);

        nu::Vector2 forward{ 1, 0 };
        forward = forward.Rotate(m_transform.rotation * nu::DegtoRad);
        AddVelocity(forward * m_speed * dt);
    }

    Actor::Update(dt);

}

void Enemy::OnCollision(Actor* other)
{
    if (other->GetTag() == "PlayerBullet") {
        SetDestoryed();

        other->SetDestoryed();

        ((SpaceGame*) m_scene->GetGame())->AddPoints(100);

        if (this->GetTag() == "ship") {
            nu::Engine::Get().GetAudio().PlaySound("ship_explosion");
        }

        if (this->GetTag() == "astroid") {
            nu::Engine::Get().GetAudio().PlaySound("astroidBreaking");
        }
    }



    for (int i = 0; i < 100; i++) {
        nu::Particle particle;
        particle.position = m_transform.position;
        particle.color = { 1.0f, 1.0f, 1.0f };
        particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
        particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

        nu::Engine::Get().GetPS().AddParticle(particle);
    }
}

void Enemy::Draw(const nu::Renderer& renderer) const {
    Actor::Draw(renderer);
}
