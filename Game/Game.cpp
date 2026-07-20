#include "Engine.h"
#include "Player.h"
#include "Enemy.h"

using namespace nu;
using namespace std;


int main()
{  

    //INITIALIZATION
    
    engine.Initialize();

    Mesh mesh{ { Vector2{-2, -4}, Vector2{-2, 4}, Vector2{5, 0}, Vector2{-2,-4}, Vector2{-4, -2}, Vector2{-4, 2}, Vector2{-2, 4} }, Color{1.0f, 0.8f, 0.4f} };
    Model model{ vector<Mesh>{ mesh} };
    
    Scene scene;
    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = model;
    playerDesc.transform = Transform{ Vector2{640.0f, 512.0f}, 0.0f, 15.0f };
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.speed = 2000.0f;

    Player* player = new Player{playerDesc};
    scene.AddActor(player);


    
    for (int i = 0; i < 20; i++) {
        Enemy* enemy = new Enemy{ 2000.0f,Transform{Vector2{840.0f, 312.0f}, 90.0f, 15.0f}, model };
        scene.AddActor(enemy);
    }
    
    std::vector<Vector2> points;

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
        engine.Update();
        float dt = engine.GetTime().GetDeltaTime();
        //player.SetRotation(player.GetTransform().rotation + (90.0f * engine.GetTime().GetDeltaTime()));
        
        scene.Update(dt);

        if (engine.GetInput().GetButtonDown(Input::MouseButton::Left)) {
            Vector2 mousePos = engine.GetInput().GetMousePosition();
            if (points.empty()) {
                points.push_back(engine.GetInput().GetMousePosition());

            }
            else {
                Vector2 v = points.back() - engine.GetInput().GetMousePosition();

                if (v.Length() > 10.0f) {
                    points.push_back(engine.GetInput().GetMousePosition());
                }
            }
        }
      
        //RENDER
		engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        engine.GetRenderer().Clear();

        // character
        scene.Draw(engine.GetRenderer());

        engine.GetRenderer().Present();
    }

    //SHUTDOWN
    engine.Shutdown();

    return 0;
}