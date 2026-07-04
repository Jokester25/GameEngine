#include "Engine.h";
#include "SDL3/SDL.h"

#include <iostream>
#include <cstdlib>


int main()
{
    const int SCREEN_W = 1280;
	const int SCREEN_H = 1024;
	const int SHAPE_COUNT = 20;
	const int FRAME_DELAY_MS = 16; // ~60 FPS

    nu::Renderer renderer;
	renderer.Initialize("Game Engine", SCREEN_W, SCREEN_H);

	srand(SDL_GetTicks()); // Seed the random number generator with the current time

    //handle Events
    SDL_Event e;
    bool quit = false;


    while (!quit) {
        Uint32 frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

		renderer.SetColor(0, 0, 0, 255); // Set render draw color to black
        renderer.Clear();

        
        for (int i = 0; i < SHAPE_COUNT; ++i) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
			int x = rand() % SCREEN_W;
			int y = rand() % SCREEN_H;
			renderer.DrawPoint(x, y);
        }
		renderer.Present();
        
        for (int i = 0; i < SHAPE_COUNT; ++i) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
            int x = rand() % SCREEN_W;
            int y = rand() % SCREEN_H;
            int x2 = rand() % SCREEN_W;
            int y2 = rand() % SCREEN_H;
            renderer.DrawLine(x, y, x2, y2);
        }
        renderer.Present();

        for (int i = 0; i < SHAPE_COUNT; ++i) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
            int x = rand() % SCREEN_W;
            int y = rand() % SCREEN_H;
            int w = rand() % 100 + 10; // Width between 10 and 110
            int h = rand() % 100 + 10; // Height between 10 and 110
            renderer.DrawRect(x, y, w, h);
		}

		renderer.Present();

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < (Uint32)FRAME_DELAY_MS) {
            SDL_Delay(16 - frameTime); // Delay to cap at ~60 FPS
		}
    }
    renderer.Shutdown();

    return 0;
}