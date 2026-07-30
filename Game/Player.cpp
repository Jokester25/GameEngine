#include "pch.h"
#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "Assets.h"
#include "Bullet.h"

void Player::Update(float dt) {

    // Move on the 2D plane without changing the ship's rotation.
    // Use WASD as world-space directions (W = up, S = down, A = left, D = right).
    nu::Vector2 dir{ 0.0f, 0.0f };
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) dir.y -= 1.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) dir.y += 1.0f;

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir.x -= 1.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir.x += 1.0f;

    nu::Vector2 velocity{ 0.0f, 0.0f };
    if (dir.x != 0.0f || dir.y != 0.0f) {
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 0.0f) {
            dir.x /= len;
            dir.y /= len;
            velocity = dir * m_speed;
        }
    }
    AddVelocity(velocity * dt);

    //particle system
    nu::Particle particle;

    nu::Vector2 offset{ -1.0f, 0.0f };
    offset = offset.Rotate(m_transform.rotation + nu::DegtoRad);

    particle.position = m_transform.position + offset;
    particle.color = { 1.0f, 1.0f, 1.0f };
    particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
    particle.velocity = { nu::RandomFloat(-200.0f, 200.0f), nu::RandomFloat(-200.0f, 200.0f) };

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
    }

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_X)) {
        
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    }


    Actor::Update(dt);

}

void Player::Draw(const nu::Renderer& renderer) const {
    renderer.DrawModel(m_model, m_transform);
}
