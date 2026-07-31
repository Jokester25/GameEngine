#pragma once
#include "Actor.h"

struct HealthPackDesc : public nu::ActorDesc {
	int amount{ 1 };
};

class HealthPack : public nu::Actor {
public:
	HealthPack() = default;
	HealthPack(const HealthPackDesc& desc) :
		Actor{ desc },
		m_amount{ desc.amount }
	{
	}
	HealthPack(float amount, const nu::Transform& transform, const nu::Model& model) :
		Actor{ transform, model },
		m_amount{ (int)amount }
	{
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	void Draw(const class nu::Renderer& renderer) const override;

private:
	int m_amount{ 1 };
};