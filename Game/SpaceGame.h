#pragma once
#include "Game.h"
#include "Text.h"
#include "Font.h"

class SpaceGame : public nu::Game
{
public:
	enum class GameState 
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver

	};
public:
	SpaceGame() = default;
	SpaceGame(nu::Scene* scene) :
		Game{ scene }
	{ }

	bool Initialize() override;

	void Update(float dt) override;
	void Draw(class nu::Renderer& renderer);

	void OnPlayerDead();
	void AddPoints(int points) { m_score += points; }
	void AddLife(int amount = 1);

private:
	void SpawnPlayer();
	void SpawnEnemy();

	void SpawnHealthPack();
private:

	int m_score{ 0 };
	int m_lives{ 0 };

	float m_stateTimer = 0.0f;

	float m_spawnTimer = 0.0f;
	float m_spawntime = 5.0f;
	int m_spawnCount = 0;

	GameState m_gameState = GameState::Title;

	nu::Font* m_titleFont{ nullptr };
	nu::Text* m_titleText{ nullptr };

	nu::Font* m_gameOverFont{ nullptr };
	nu::Text* m_gameOverText{ nullptr };

	nu::Font* m_gameFont{ nullptr };

	nu::Text* m_scoreText{ nullptr };
	nu::Text* m_livesText{ nullptr };

	nu::Text* m_CurrentSongText{ nullptr };
};