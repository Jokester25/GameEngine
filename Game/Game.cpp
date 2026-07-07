#include "Engine.h";


using namespace nu;
using namespace std;


int main()
{   
    //INITIALIZATION
    const int SCREEN_W = 1280;
	const int SCREEN_H = 1024;
	const int SHAPE_COUNT = 20;

    Input input;
    input.Initialize();

	//std::cout << sizeof(Vector2) << std::endl;
    Vector2 vel(0.5f, 0.5f);
    std::vector<Vector2> v;
    
    for (int i = 0; i < 300; ++i) {
		v.push_back(Vector2{ RandomFloat(SCREEN_W), RandomFloat(SCREEN_H) });
    }

    Renderer renderer;
	renderer.Initialize("Game Engine", SCREEN_W, SCREEN_H);

    //Main Loop
    bool quit = false;
    while (!quit) {
        //Update
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        input.Update();
        
        if (input.GetKeyDown(SDL_SCANCODE_Q)) { cout << "pressed q" << endl; };

        //RENDER
		renderer.SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        renderer.Clear();

		// Draw random points
        for (int i = 0; i < v.size(); ++i) {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), 255);
            //v[i] = v[i] + vel;
			renderer.DrawPoint(v[i].x, v[i].y);
        }
		renderer.Present();

		renderer.SetColor(1.0f, 1.0f, 1.0f); 
        renderer.DrawRect(input.GetMousePosition().x - 20, input.GetMousePosition().y - 20, 40, 40);
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