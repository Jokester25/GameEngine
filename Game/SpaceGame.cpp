#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

using namespace nu;
using namespace assets;

bool SpaceGame::Initialize()
{
    Game::Initialize();

    m_scene = new Scene();

    m_titleFont = new Font();
    m_titleFont->Load("Fonts/OldLondon.ttf", 64);

    m_titleText = new Text(m_titleFont);
    m_titleText->Create(Engine::Get().GetRenderer(), "Space Training", Color{ 1.0f, 1.0f, 1.0f });

    m_gameFont = new Font();
    m_gameFont->Load("Fonts/OldLondon.ttf", 32);
    
    m_scoreText = new Text(m_gameFont);

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
        m_gameState = GameState::StartLevel;
        break;
    case GameState::StartLevel:
        SpawnPlayer();
        m_gameState = GameState::Game;
    break;
    case GameState::Game:
        break;
    case GameState::GameOver:
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
        m_scoreText->Draw(renderer, 30.0f, 30.0f);
        break;
    case GameState::GameOver:
        //Draw Game Over
        break;
    default:
        break;
    }
    Game::Draw(renderer);
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
    
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = playerModel;
        enemyDesc.transform = Transform{ Vector2{RandomFloat(320.0f),RandomFloat(200.0f)}, RandomFloat(25.0f,90.0f), RandomFloat(5.0f,15.0f) };
        enemyDesc.velocity = Vector2{ 0.0f, 0.0f };
        enemyDesc.speed = 2000.0f;
        enemyDesc.damping = 3.0f;
        Enemy* enemy = new Enemy{ enemyDesc };

        m_scene->AddActor(enemy);
}
