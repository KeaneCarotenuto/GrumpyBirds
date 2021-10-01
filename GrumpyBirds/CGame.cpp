#include "CGame.h"

CGame *CGame::m_instance = nullptr;

CGame::~CGame()
{
}

/// <summary>
/// Basic constructor
/// <para>Author: Keane</para>
/// </summary>
CGame::CGame()
{
	b2Vec2 gravity = b2Vec2(0.0, -9.81f);
	m_world = new b2World(gravity);
	m_world->SetContactListener(&m_collisionDetector);
}

/// <summary>
/// Returns singleton
/// <para>Author: Keane</para>
/// </summary>
/// <returns></returns>
CGame *CGame::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CGame();
	}

	return m_instance;
}

/// <summary>
/// Change the level
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_newLevel"></param>
void CGame::SetLevel(Level _newLevel)
{
	m_currentLevel = _newLevel;
	Clear();
	Init();
}

/// <summary>
/// Initialises level when changing
/// <para>Author: Keane</para>
/// </summary>
void CGame::Init()
{
	if (m_isInitialised)
		return;
	m_isInitialised = true;

	m_gameClock.restart();

	switch (m_currentLevel)
	{
	case Level::One:
	{

		sf::Vector2f shootPos = {200, 100};

		CBird *bird1 = new CBird(m_world, {100, 35}, 25, b2_dynamicBody, "Bird_Fast_1.png", CBird::BirdType::Fast);
		m_allBirds.push_back(bird1);
		bird1->SetShootPos(shootPos);

		CBird *bird2 = new CBird(m_world, {50, 35}, 25, b2_dynamicBody, "Bird_Regular_1.png", CBird::BirdType::Regular);
		m_allBirds.push_back(bird2);
		bird2->SetShootPos(shootPos);

		CPig *pig1 = new CPig(m_world, {800, 500}, 25, b2_dynamicBody, "Pig_Regular_1.png");
		m_allPigs.push_back(pig1);

		CDestructibleBlock *anchor = new CDestructibleBlock(m_world, {800, 400}, {10, 10}, b2_staticBody, "Block_Wood_Regular_1.png");
		m_allBlocks.push_back(anchor);
		CDestructibleBlock *rectBody = new CDestructibleBlock(m_world, {800, 800}, {100, 20}, b2_dynamicBody, "Block_Wood_Regular_1.png");
		m_allBlocks.push_back(rectBody);
		CDestructibleBlock *rectBody2 = new CDestructibleBlock(m_world, {800, 800}, {100, 20}, b2_dynamicBody, "Block_Wood_Regular_1.png");
		m_allBlocks.push_back(rectBody2);
		CDestructibleBlock *rectBody3 = new CDestructibleBlock(m_world, {800, 800}, {100, 20}, b2_dynamicBody, "Block_Wood_Regular_1.png");
		m_allBlocks.push_back(rectBody3);
		CDestructibleBlock *circleBody = new CDestructibleBlock(m_world, {800, 700}, 40, b2_dynamicBody, "Block_Wood_Circle_1.png");
		m_allBlocks.push_back(circleBody);

		b2RevoluteJointDef revoluteJointDef1;
		revoluteJointDef1.bodyA = anchor->GetBody();
		revoluteJointDef1.bodyB = rectBody->GetBody();
		revoluteJointDef1.collideConnected = false;
		revoluteJointDef1.localAnchorA.Set(0, 0);
		revoluteJointDef1.localAnchorB.Set(50 / SCALE, 0 / SCALE);
		m_world->CreateJoint(&revoluteJointDef1);

		b2RevoluteJointDef revoluteJointDef2;
		revoluteJointDef2.bodyA = rectBody->GetBody();
		revoluteJointDef2.bodyB = rectBody2->GetBody();
		revoluteJointDef2.collideConnected = false;
		revoluteJointDef2.localAnchorA.Set(-50 / SCALE, 0 / SCALE);
		revoluteJointDef2.localAnchorB.Set(50 / SCALE, 0 / SCALE);
		m_world->CreateJoint(&revoluteJointDef2);

		b2RevoluteJointDef revoluteJointDef3;
		revoluteJointDef3.bodyA = rectBody2->GetBody();
		revoluteJointDef3.bodyB = rectBody3->GetBody();
		revoluteJointDef3.collideConnected = false;
		revoluteJointDef3.localAnchorA.Set(-50 / SCALE, 0 / SCALE);
		revoluteJointDef3.localAnchorB.Set(50 / SCALE, 0 / SCALE);
		m_world->CreateJoint(&revoluteJointDef3);

		b2RevoluteJointDef revoluteJointDef4;
		revoluteJointDef4.bodyA = rectBody3->GetBody();
		revoluteJointDef4.bodyB = circleBody->GetBody();
		revoluteJointDef4.collideConnected = false;
		revoluteJointDef4.localAnchorA.Set(-50 / SCALE, 0 / SCALE);
		revoluteJointDef4.localAnchorB.Set(0, 0);
		m_world->CreateJoint(&revoluteJointDef4);

		CBody *myGround = new CBody(m_world, {800, -100}, {1600, 215}, b2_staticBody, "ground.png");
		m_allGround.push_back(myGround);
		CBody *myGrass = new CBody(m_world, {800, 15}, {1600, 28}, b2_staticBody, "grass.png");
		m_allGround.push_back(myGrass);
		myGrass->GetBody()->GetFixtureList()->SetSensor(true);

		CBody *slingImg = new CBody(m_world, shootPos, {10, 10}, b2_staticBody, "Circle.png");
		m_allGround.push_back(slingImg);
		slingImg->GetBody()->GetFixtureList()->SetSensor(true);

		FindNewShooter();

		break;
	}

	case Level::Two:
	{

		CBird *circleBody = new CBird(m_world, {426, 800}, 25, b2_dynamicBody, "Circle.png", CBird::BirdType::Fast);
		m_allBirds.push_back(circleBody);
		//CBody* squareBody = new CBody(m_world, { 200,300 }, { 50,50 }, b2_dynamicBody, "Rect.png");						m_allBlocks.push_back(squareBody);

		CBody *myGround = new CBody(m_world, {400, 100}, {750, 100}, b2_staticBody, "Rect.png");
		m_allGround.push_back(myGround);
		myGround->GETBODY_TODELETE()->SetTransform(myGround->GETBODY_TODELETE()->GetPosition(), 10 * ((float)M_PI / 180.0f));
		break;
	}

	default:
		break;
	}
}

/// <summary>
/// Find bird to be shot
/// <para>Author: Keane</para>
/// </summary>
void CGame::FindNewShooter()
{
	m_currentShooter = nullptr;

	for (CBird *_bird : m_allBirds)
	{
		if (_bird->GetState() == CBird::BirdState::Waiting)
		{
			m_currentShooter = _bird;
			_bird->SetState(CBird::BirdState::Shooting);
			break;
		}
	}
}

void CGame::ClearDeleted()
{
	m_allBirds.erase(std::remove_if(m_allBirds.begin(), m_allBirds.end(), [](CBird *_body)
									{ return _body->IsDeleting(); }),
					 m_allBirds.end());
	m_allPigs.erase(std::remove_if(m_allPigs.begin(), m_allPigs.end(), [](CPig *_body)
								   { return _body->IsDeleting(); }),
					m_allPigs.end());
	m_allBlocks.erase(std::remove_if(m_allBlocks.begin(), m_allBlocks.end(), [](CDestructibleBlock *_body)
									 { return _body->IsDeleting(); }),
					  m_allBlocks.end());
	m_allGround.erase(std::remove_if(m_allGround.begin(), m_allGround.end(), [](CBody *_body)
									 { return _body->IsDeleting(); }),
					  m_allGround.end());
}

/// <summary>
/// Clears level
/// <para>Author: Keane</para>
/// </summary>
void CGame::Clear()
{
	if (!m_isInitialised)
		return;

	for (CBird *_body : m_allBirds)
	{
		if (_body)
			_body->Destroy();
	};
	m_allBirds.clear();
	for (CPig *_body : m_allPigs)
	{
		if (_body)
			_body->Destroy();
	};
	m_allPigs.clear();
	for (CDestructibleBlock *_body : m_allBlocks)
	{
		if (_body)
			_body->Destroy();
	};
	m_allBlocks.clear();
	for (CBody *_body : m_allGround)
	{
		if (_body)
			_body->Destroy();
	};
	m_allGround.clear();

	m_isInitialised = false;
}

/// <summary>
/// Fixed update for level
/// <para>Author: Keane</para>
/// </summary>
void CGame::FixedUpdate()
{
	if (!m_isInitialised)
		return;

	for (CBody *_body : CBody::GetAllBodies())
	{
		_body->FixedUpdate();
	}

	if (m_currentShooter == nullptr)
	{

		if (m_timeout == 0)
		{
			m_timeout = m_gameClock.getElapsedTime().asSeconds();
		}
		else
		{
			if (m_gameClock.getElapsedTime().asSeconds() - m_timeout >= m_maxTimeout)
			{
				Clear();
			}
		}
	}
	else
	{
		if (m_currentShooter->GetState() != CBird::BirdState::Shooting)
			FindNewShooter();
	}

	if (m_world)
		m_world->Step((float)timeStep, velocityIterations, positionIterations);
}

/// <summary>
/// Draws any temporary objects, then deletes them
/// <para>Author: Keane</para>
/// </summary>
void CGame::DrawAllTemps()
{
	if (!m_window)
		return;

	for (sf::Drawable *_drawable : m_toDraw)
	{
		m_window->draw(*_drawable);
		delete _drawable;
	}
	m_toDraw.clear();
}