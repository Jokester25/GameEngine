#pragma once
#include <vector>

using namespace std;
namespace nu
{
	class Actor;

	class Scene {
	
	public:
		void AddActor(Actor* actor) { m_actors.push_back(actor); }

		void Update(float dt);
		void Draw(const class Renderer& renderer);

	private:
		vector<Actor*> m_actors;
		
	};
}