#ifndef CGAME_H
#define CGAME_H

#include <vector>

#include "CBody.h"
#include "CBird.h"
#include "utility.h"
#include "CCollision.h"

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
	void FindNewShooter();
	void Clear();
	void FixedUpdate();

	b2World* GetWorld() { return m_world; };

private:
	CGame();
	~CGame();

	static CGame* m_instance;

	sf::RenderWindow* m_window;

	CGame::Level m_currentLevel = Level::One;

	std::vector<CBird*> m_allBirds;
	std::vector<CBody*> m_allBlocks;
	std::vector<CBody*> m_allGround;

	CBird* m_currentShooter = nullptr;

	sf::Clock m_gameClock;
	float m_timeout = 0;
	float m_maxTimeout = 5;

	CCollision m_collisionDetector;

	b2World* m_world = nullptr;

	double timeStep = (1.0f / 60.0f);
	int32 velocityIterations = 8;
	int32 positionIterations = 8;

	bool m_isInitialised = false;
};

#endif