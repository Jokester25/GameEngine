#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "HealthPack.h"

using namespace nu;
using namespace assets;

bool SpaceGame::Initialize()
{
    Game::Initialize();

    m_scene = new Scene();
    m_scene->SetGame(this);

    Engine::Get().GetAudio().AddSound("BackgroundMusic", "audio/Sneaky_Snitch.mp3");
    Engine::Get().GetAudio().AddSound("ship_explosion", "audio/explosion_with_debris.mp3");
    Engine::Get().GetAudio().AddSound("item-pickup", "audio/duck-toy.mp3");
    Engine::Get().GetAudio().AddSound("astroidBreaking", "audio/rock-destroy.mp3");
    Engine::Get().GetAudio().AddSound("lazer", "audio/blaster_shot.mp3");


    Engine::Get().GetAudio().PlaySound("BackgroundMusic");
   
    m_titleFont = new Font();
    m_titleFont->Load("Fonts/OldLondon.ttf", 64);

    m_titleText = new Text(m_titleFont);
    m_titleText->Create(Engine::Get().GetRenderer(), "Space Training", Color{ 1.0f, 1.0f, 1.0f });

    m_gameFont = new Font();
    m_gameFont->Load("Fonts/OldLondon.ttf", 32);
    
    m_scoreText = new Text(m_gameFont);
    m_livesText = new Text(m_gameFont);
    m_CurrentSongText = new Text(m_gameFont);

    return true;
}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {
    case GameState::Title:
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;

        }
        break;
    case GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_spawntime = 5.0f;
        m_stateTimer = 0.5f;
        m_gameState = GameState::StartLevel;
        break;
    case GameState::StartLevel:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_scene->RemoveAllActor();
            SpawnPlayer();
            m_gameState = GameState::Game;
        }
      
        break;

    case GameState::Game:
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0.0f) {
            m_spawnTimer = m_spawntime;
            SpawnEnemy();
            if (RandomFloat(0.0f, 1.0f) < 0.50f) {
                SpawnHealthPack();
            }
            m_spawnCount++;
            if (m_spawnCount > 5) {
                m_spawnCount = 0;
                m_spawntime -= 0.0f;
            }
        }

        
        break;
    case GameState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_scene->RemoveAllActor();
            m_gameState = GameState::Title;
        }
        break;
    default:
        break;

    }
    Game::Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
    switch (m_gameState)
    {
    case GameState::Title:
        //Draw title
        m_titleText->Draw(renderer, 40.0f, 40.0f);
        break;
    case GameState::StartGame:
    case GameState::StartLevel:
    case GameState::Game:
        // draw score / lives
        m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
        m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
        m_scoreText->Draw(renderer, 30.0f, 30.0f);
        m_livesText->Draw(renderer, renderer.GetWidth() - 110, 30.0f);

        break;
    case GameState::GameOver:
        //Draw Game Over
        
        break;
    default:
        break;
    }
    Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead()
{
    m_lives--;
    m_gameState = (m_lives == 0) ? GameState::GameOver : GameState::StartLevel;
    
    m_stateTimer = 2.0f;


}

void SpaceGame::AddLife(int amount){
    m_lives += amount;
    Engine::Get().GetAudio().PlaySound("item-pickup");
}

void SpaceGame::SpawnPlayer()
{
        PlayerDesc playerDesc;
        playerDesc.name = "Player";
        playerDesc.model = playerModel;
        playerDesc.transform = Transform{ Vector2{640.0f, 512.0f}, 0.0f, 15.0f };
        playerDesc.velocity = Vector2{ 0.0f, 0.0f };
        playerDesc.speed = 2000.0f;
        playerDesc.damping = 2.0f;
        Player* player = new Player{ playerDesc };
        m_scene->AddActor(player);   
}

void SpaceGame::SpawnEnemy()
{       
        float spawnX = Engine::Get().GetRenderer().GetWidth() + RandomFloat(10.0f, 50.0f);
        float spawnY = RandomFloat(0.0f, (float)Engine::Get().GetRenderer().GetHeight());
        int modelIndex = RandomInt(2);

        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        if (modelIndex == 0) {
        enemyDesc.model = enemyModel;
        enemyDesc.tag = "ship";
        }
        else {
        enemyDesc.model = astroidModel;
        enemyDesc.tag = "astroid";
        }   

        enemyDesc.transform = Transform{ Vector2{spawnX, spawnY}, RandomFloat(25.0f, 90.0f), RandomFloat(5.0f, 15.0f) };
        enemyDesc.velocity = Vector2{ 0.0f, 0.0f };
        enemyDesc.speed = 2000.0f;
        enemyDesc.damping = 3.0f;
        Enemy* enemy = new Enemy{ enemyDesc };

        m_scene->AddActor(enemy);
}

void SpaceGame::SpawnHealthPack()
{
    HealthPackDesc desc;
    desc.name = "HealthPack";
    desc.tag = "health";
    desc.model = assets::medPackModel;
    float x = RandomFloat(100.0f, (float)Engine::Get().GetRenderer().GetWidth() - 100.0f);
    float y = RandomFloat(100.0f, (float)Engine::Get().GetRenderer().GetHeight() - 100.0f);
    desc.transform = Transform{ Vector2{ x, y }, 0.0f, 10.0f };
    desc.lifespan = 30.0f; 
    desc.amount = 1;

    HealthPack* hp = new HealthPack{ desc };
    m_scene->AddActor(hp);
}