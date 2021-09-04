#pragma once
#include <vector>

#include "CBody.h"
#include "utility.h"

class CGame
{
public:
	enum class Level {
		One = 1,
		Two
	};

	static CGame* GetInstance();

	void SetWindow(sf::RenderWindow* _wind) { m_window = _wind; };
	sf::RenderWindow* GetWindow() { return m_window; };

	void SetLevel(Level _newLevel);

	void Init();
	void Clear();
	void FixedUpdate();

	b2World* GetWorld() { return m_world; };

private:
	CGame();
	~CGame();

	static CGame* m_instance;

	sf::RenderWindow* m_window;

	CGame::Level m_currentLevel = Level::One;

	std::vector<CBody*> m_allBirds;
	std::vector<CBody*> m_allBlocks;
	std::vector<CBody*> m_allGround;

	b2World* m_world = nullptr;

	double timeStep = (1.0f / 60.0f);
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	bool m_isInitialised = false;
};