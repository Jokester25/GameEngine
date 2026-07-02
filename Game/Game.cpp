#include "Engine.h";
#include "SDL3/SDL.h"

#include <iostream>


int main()
{
    nu::Renderer renderer;
	renderer.Initialize("Game Engine", 1280, 1024);

    //handle Events
    SDL_Event e;
    bool quit = false;


    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

		renderer.SetColor(0, 0, 0, 255); // Set render draw color to black
        renderer.Clear();

        for(int i = 0; i < 100; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
            renderer.DrawPoint(rand() % 1280, rand() % 1024);
		}

		renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
        renderer.DrawFillRect(40, 40, 50, 50);

		renderer.Present();
    }
    renderer.Shutdown();

    return 0;
}