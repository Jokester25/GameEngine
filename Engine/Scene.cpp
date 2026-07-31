#include "pch.h"
#include "Scene.h"
#include "Actor.h"
namespace nu 
{	
	void Scene::AddActor(Actor* actor) { 
		actor->m_scene = this;
		m_pendingActors.push_back(actor); 
	}

	void Scene::RemoveAllActor()
	{
		for (auto actor : m_actors) {
			delete actor;
		}
		m_actors.clear();
	}

	void Scene::Update(float dt) {
		// update actors
		for (auto actor : m_actors) {
			actor->Update(dt);
		}

		//update colisions
		UpdateCollisions();

		//remove destroyed actors
		std::erase_if(m_actors, [](auto actor) {return actor->m_destoryed; } );

		//add pending actors
		m_actors.insert(m_actors.end(), m_pendingActors.begin(), m_pendingActors.end());
		m_pendingActors.clear();
	}

	void Scene::Draw(const class Renderer& renderer) {
		for (auto actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	void Scene::UpdateCollisions() {

		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || actorA->m_destoryed || actorB->m_destoryed) continue;

				//checks colliions
				float distance = (actorA->m_transform.position - actorB->m_transform.position).Length();

				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
					actorA->OnCollision(actorB);
					actorB->OnCollision(actorA);
				}

			}
		}
	}

}