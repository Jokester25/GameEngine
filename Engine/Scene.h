#pragma once
#include "Actor.h"

#include <vector>
#include <string>


using namespace std;
namespace nu
{
	class Scene {
	
	public:
		void AddActor(Actor* actor);

		void Update(float dt);
		void Draw(const class Renderer& renderer);

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

	private:
		vector<Actor*> m_actors;
		
	};

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name){

		for (auto actor : m_actors) {

			T* actorT = dynamic_cast<T*>(actor);

			if (actorT && actorT->m_name == name) {
				return actorT;
			}

		}
		return nullptr;
	}

}