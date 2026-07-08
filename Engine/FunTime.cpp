#include "pch.h"
#include "FunTime.h"

#include <SDL3/SDL.h>

namespace nu
{
	Time::Time() {
		Rest();
	}

	void Time::Rest() {
		m_startTicks = SDL_GetTicksNS();
		m_currentTicks = SDL_GetTicksNS();
		m_frameTicks = SDL_GetTicksNS();
	}

	void Time::Tick() {
		m_currentTicks = SDL_GetTicksNS();
		m_deltaTicks = m_currentTicks - m_frameTicks;
		m_frameTicks = m_currentTicks;
	}
}
