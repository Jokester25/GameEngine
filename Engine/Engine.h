#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Random.h"
#include "EnginMath.h"
#include "Transform.h"
//#include "Mesh.h"

#include "Actor.h"
#include "Scene.h"
#include "Game.h"
#include "ParticleSystem.h"

#include "Text.h"

#include "Audio.h"

//systems
#include "Renderer.h"
#include "Input.h"
#include "FunTime.h"
#include "File.h"

#include <iostream>
#include <vector>
#include <cstdlib>

namespace nu
{
	class Engine {
	public:
		static Engine& Get() { static Engine engine; return engine; }
		
		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }

		Audio& GetAudio() { return m_audio; }
		ParticleSystem& GetPS() { return m_particleSystem; }

	private:
		Engine() = default;

	private:
		Input m_input;
		Renderer m_renderer;
		Time m_time;
		Audio m_audio;
		ParticleSystem m_particleSystem;


	};
}