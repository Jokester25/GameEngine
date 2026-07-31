#include "pch.h"
#include "HealthPack.h"
#include "Renderer.h"
#include "Engine.h"
#include "SpaceGame.h"
#include "Assets.h"

void HealthPack::Update(float dt) {
	// simple rotation for visibility (optional)
	m_transform.rotation += 90.0f * dt;
	Actor::Update(dt);
}

void HealthPack::OnCollision(Actor* other) {
	// only react to player pickups
	if (other->GetName() == "Player") {
		// mark picked up
		SetDestoryed();

		// increase lives on the game
		auto game = (SpaceGame*)m_scene->GetGame();
		if (game) {
			game->AddLife(m_amount);
		}

		// play pickup sound
		nu::Engine::Get().GetAudio().PlaySound("item-pickup");
	}
}

void HealthPack::Draw(const nu::Renderer& renderer) const {
	renderer.DrawModel(m_model, m_transform);
}