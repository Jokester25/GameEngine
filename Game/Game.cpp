#include "Engine.h";


using namespace nu;
using namespace std;


int main()
{   
    //INITIALIZATION
    Renderer renderer;
    const int SCREEN_W = 1280;
	const int SCREEN_H = 1024;
    renderer.Initialize("Game Engine", SCREEN_W, SCREEN_H);

    Input input;
    input.Initialize();

    Time time;

    Vector2 position{ 640.0f, 512.0f };
    std::vector<Vector2> points;
    float speed = 400.0f;

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
        //engine
        input.Update();
        time.Tick();
        
      //  cout << seconds << " " << dt << endl;
        
      //if (input.GetKeyPressed(SDL_SCANCODE_Q)) { cout << "pressed" << endl; };
	  //if (input.GetKeyDown(SDL_SCANCODE_Q)) { cout << "down" << endl; };
	  //if (input.GetKeyReleased(SDL_SCANCODE_Q)) { cout << "released" << endl; };

		//if (input.GetButtonDown(Input::MouseButton::Left)) { cout << "Mouse Left Button down" << endl; }
		//if (input.GetButtonPressed(Input::MouseButton::Left)) { cout << "Mouse Left Button pressed" << endl; }
		//if (input.GetButtonReleased(Input::MouseButton::Left)) { cout << "Mouse Left Button Released" << endl; }

        if (input.GetButtonPressed(Input::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }

        Vector2 velocity{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) velocity.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) velocity.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) velocity.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) velocity.y = +speed;

        position += (velocity * time.GetDeltaTime());

        //RENDER
		renderer.SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        renderer.Clear();

		// Draw random points
        for (int i = 0; i < points.size(); ++i) {
            //renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), 255);
            renderer.SetColor(1.0f, 1.0f, 1.0f);
			renderer.DrawFillRect(points[i].x, points[i].y, 10.0f, 10.0f);
        }

        // character
		renderer.SetColor(1.0f, 1.0f, 1.0f); 
        renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);
		
        renderer.Present();
    }

    //SHUTDOWN
    renderer.Shutdown();

    return 0;
}