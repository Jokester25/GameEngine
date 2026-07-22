#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>

using namespace nu;
using namespace std;


int main()
{  

    //INITIALIZATION
    
    engine.Initialize();

    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = nu::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = nu::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = nu::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    nu::WriteTextFile("test.txt", "Hello, World!", true);
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
    audio->createSound("whistle.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("scream.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("oof.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("duck-toy.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("hee-hee.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);
    

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


        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_4))
        {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_5))
        {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }

        audio->update();

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