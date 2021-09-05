#include "CGame.h"

CGame* CGame::m_instance = nullptr;

CGame::~CGame()
{
}

CGame::CGame()
{
	b2Vec2 gravity = b2Vec2(0.0, -9.81f);
	m_world = new b2World(gravity);
	m_world->SetContactListener(&m_collisionDetector);
}

CGame* CGame::GetInstance()
{
	if (m_instance == nullptr) {
		m_instance = new CGame();
	}

	return m_instance;
}

void CGame::SetLevel(Level _newLevel)
{
	m_currentLevel = _newLevel;
	Clear();
	Init();
}

void CGame::Init()
{
	if (m_isInitialised) return;
	m_isInitialised = true;

	switch (m_currentLevel)
	{
	case Level::One: {

		CBird* bird1 = new CBird(m_world, { 226,800 }, 25, b2_dynamicBody, "Circle.png");				m_allBirds.push_back(bird1);
		CBody* squareBody = new CBody(m_world, { 200,700 }, { 50,50 }, b2_dynamicBody, "Rect.png");		m_allBlocks.push_back(squareBody);
		CBody* rectBody = new CBody(m_world, { 226,800 }, { 100,50 }, b2_dynamicBody, "Rect.png");		m_allBlocks.push_back(rectBody);

		CBody* myGround = new CBody(m_world, { 400,100 }, { 750,100 }, b2_staticBody, "Rect.png");		m_allGround.push_back(myGround);

		break;
	}

	case Level::Two: {

		CBird* circleBody = new CBird(m_world, { 426,800 }, 25, b2_dynamicBody, "Circle.png");							m_allBirds.push_back(circleBody);
		CBody* squareBody = new CBody(m_world, { 200,300 }, { 50,50 }, b2_dynamicBody, "Rect.png");						m_allBlocks.push_back(squareBody);
																														
		CBody* myGround = new CBody(m_world, { 400,100 }, { 750,100 }, b2_staticBody, "Rect.png");						m_allGround.push_back(myGround);
		myGround->GETBODY_TODELETE()->SetTransform(myGround->GETBODY_TODELETE()->GetPosition(), 10 * (M_PI / 180.0));
		break;
	}

	default:
		break;
	}
}

void CGame::Clear()
{
	if (!m_isInitialised) return;

	for (CBird* _body : m_allBirds) { _body->Destroy(); };		m_allBirds.clear();
	for (CBody* _body : m_allBlocks) { _body->Destroy(); };		m_allBlocks.clear();
	for (CBody* _body : m_allGround) { _body->Destroy(); };		m_allGround.clear();

	m_isInitialised = false;
}

void CGame::FixedUpdate()
{
	if (!m_isInitialised) return;

	for (CBody* _body : CBody::GetAllBodies()) {
		_body->FixedUpdate();
	}

	if (m_world) m_world->Step(timeStep, velocityIterations, positionIterations);
}
