#include "Engine.h";

#include <iostream>
#include <cstdlib>
using namespace nu;

int main()
{   
    //INITIALIZATION
    const int SCREEN_W = 1280;
	const int SCREEN_H = 1024;
	const int SHAPE_COUNT = 20;

	std::cout << sizeof(Vector2) << std::endl;
    Vector2 v[300];
    for (int i = 0; i < 30; ++i) {
		v[i].x = RandomFloat(SCREEN_W);
        v[i].y = RandomFloat(SCREEN_H);
    }

    Renderer renderer;
	renderer.Initialize("Game Engine", SCREEN_W, SCREEN_H);

	srand(SDL_GetTicks()); 

    //Main Loop
    bool quit = false;
    while (!quit) {
        //Update
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        //RENDER
		renderer.SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        renderer.Clear();

		// Draw random points
        for (int i = 0; i < SHAPE_COUNT; ++i) {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), 255);
			renderer.DrawPoint(v[i].x, v[i].y);
        }
		renderer.Present();
        
        //Draw random Lines
        /*
        for (int i = 0; i < SHAPE_COUNT; ++i) {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), 255);
            int x = RandomFloat(SCREEN_W);//rand() % SCREEN_W;
            int y = RandomFloat(SCREEN_H);
            int x2 = RandomFloat(SCREEN_W);
            int y2 = RandomFloat(SCREEN_H);
            renderer.DrawLine(x, y, x2, y2);
        }
        renderer.Present();

        //Draw random Rectangles
        for (int i = 0; i < SHAPE_COUNT; ++i) {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), 255);
            int x = rand() % SCREEN_W;
            int y = rand() % SCREEN_H;
            int w = RandomFloat(100, 10);
            int h = rand() % 100 + 10;
            renderer.DrawRect(x, y, w, h);
		}
        
		renderer.Present();
        */
    }
    //SHUTDOWN
    renderer.Shutdown();

    return 0;
}