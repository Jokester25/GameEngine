#include "pch.h"
#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "Assets.h"
#include "Bullet.h"
#include "SpaceGame.h"

void Player::Update(float dt) {
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);
    nu::Vector2 forward{ 1,0 };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegtoRad) * thrust;
    AddVelocity(velocity * dt);

    //particle system
    nu::Particle particle;

    nu::Vector2 offset{ -20.0f, 0.0f };
    offset = offset.Rotate(m_transform.rotation + nu::DegtoRad);

    nu::Color colors[3] = { {1.0f, 1.0f,1.0f}, {0.9f, 0.2f,1.0f}, {0.9f, 0.8f, 0.0f}, };
    particle.position = m_transform.position + offset;
    particle.color = colors[nu::RandomInt(3)];
    particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
    particle.velocity = nu::Vector2{-30.0f, 0.0f}.Rotate(m_transform.rotation + nu::DegtoRad);

    nu::Engine::Get().GetPS().AddParticle(particle);

    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
        BulletDesc desc;
        desc.name = "Bullet";
        desc.tag = "PlayerBullet";
        desc.model = assets::bulletModel;
        desc.transform = m_transform;
        desc.speed = 1000.0f;
        desc.lifespan = 5.0f;

        Bullet* bullet = new Bullet{ desc };
        m_scene->AddActor(bullet);

        desc.transform.rotation += 10.0f;
        bullet = new Bullet{ desc };
        m_scene->AddActor(bullet);

        desc.transform.rotation += 10.0f;
        bullet = new Bullet{ desc };
        m_scene->AddActor(bullet);

        Engine::Get().GetAudio().PlaySound("lazer");
    }

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_X)) {
        
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    }


    Actor::Update(dt);

}

void Player::OnCollision(Actor* other) {
    if (other->GetName() == "Enemy") {
        SetDestoryed();
        ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
    }
}


void Player::Draw(const nu::Renderer& renderer) const {
    renderer.DrawModel(m_model, m_transform);
}
