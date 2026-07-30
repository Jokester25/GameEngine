#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"

#include <fmod.hpp>
#include <map>
#include <string>

using namespace nu;
using namespace std;
using namespace assets;


int main()
{   
    SetWorkingDirectory("Assets");
    //INITIALIZATION   
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();
    
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
        Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();
        //player.SetRotation(player.GetTransform().rotation + (90.0f * engine.GetTime().GetDeltaTime()));
        
        game.Update(dt);
      
        //RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        Engine::Get().GetRenderer().Clear();

        // character
        game.Draw(Engine::Get().GetRenderer());
       

        //Engine::Get().GetPS.Draw(); <-- for the particle system
        Engine::Get().GetRenderer().Present();

    }

    //SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}