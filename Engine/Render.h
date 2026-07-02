#pragma once

#include <SDL3/SDL.h>

namespace nu
{
	class Renderer
	{
	public :
		bool Initialize(const char* name, int width, int height);
		void Shutdown();

		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha = 255);
		void Clear();
		void Present();
		
		void DrawPoint(float x, float y);
		void DrawFillRect(float x, float y, float w, float h);
		void DrawRect(float x, float y, float w, float h);
	private:
		//m_(insert name) is a naming convention for member variables
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
	};
}
