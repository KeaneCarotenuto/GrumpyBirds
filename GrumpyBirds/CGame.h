// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2021 Media Design School
//
// File Name   : CGame.h
// Description : Main Game management class
// Authors     : Keane Carotenuto
// Mail        : KeaneCarotenuto@gmail.com

#ifndef CGAME_H
#define CGAME_H

#include <vector>

#include "CBody.h"
#include "CBird.h"
#include "CPig.h"
#include "CDestructibleBlock.h"
#include "utility.h"
#include "CCollision.h"

/// <summary>
/// Game class to manage the current level. Stores birds, pigs, blocks, world, and nearly everything needed for a level to work.
/// <para>Author: Keane</para>
/// </summary>
class CGame
{
public:
	enum class Level
	{
		One = 1,
		Two
	};

	static CGame *GetInstance();

	void SetWindow(sf::RenderWindow *_wind) { m_window = _wind; };
	sf::RenderWindow *GetWindow() { return m_window; };

	void SetLevel(Level _newLevel);

	void AddBird(CBird* _bird) { if (_bird) m_allBirds.push_back(_bird); };

	void Init();
	void FindNewShooter();
	void ClearDeleted();
	void Clear();
	void FixedUpdate();

	/// <summary>
	/// Assigns object to be drawn this frame, then deleted immediately.
	/// <para>Author: Keane</para>
	/// </summary>
	/// <param name="_item"></param>
	void DrawTempItem(sf::Drawable *_item)
	{
		if (_item)
			m_toDraw.push_back(_item);
	};

	void DrawAllTemps();

	b2World *GetWorld() { return m_world; };

private:
	CGame();
	~CGame();

	void PlaceLevel(char _arr[][20]);

	static CGame *m_instance;

	sf::RenderWindow *m_window = nullptr;

	CGame::Level m_currentLevel = Level::One;

	std::vector<CBird *> m_allBirds;
	std::vector<CPig *> m_allPigs;
	std::vector<CDestructibleBlock *> m_allBlocks;
	std::vector<CBody *> m_allGround;

	std::vector<sf::Drawable *> m_toDraw;

	CBird *m_currentShooter = nullptr;

	sf::Clock m_gameClock;
	float m_timeout = 0;
	float m_maxTimeout = 5;

	CCollision m_collisionDetector;

	b2World *m_world = nullptr;

	double timeStep = (1.0f / 60.0f);
	int32 velocityIterations = 8;
	int32 positionIterations = 8;

	bool m_isInitialised = false;
};

#endif