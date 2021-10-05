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
/// Parse a 2D char array and build a Level layout from it
/// [Wood/Stone] - Wood is breakable Stone is not.
/// [b/B] = Block       [o/O] = Circle       [P] = Pig 
/// [[/{] = Left pillar []/}] = Right pillar [l/|] = Pillar
/// [_/=] = Platform 
/// <para>Author: Nerys</para>
/// </summary>
/// <param name="_arr">A 2D array of characters</param>
void CGame::PlaceLevel(char _arr[][20])
{
	float heightmult = 50.0f;
	float widthmult = 50.0f;

	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			CDestructibleBlock *block;
			CPig *pig;
			switch (_arr[i][j])
			{
			case 'B':
				block = new CDestructibleBlock(m_world, {(j+10) * widthmult, 825.0f - (i * heightmult)}, {50, 50}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
				m_allBlocks.push_back(block);
				break;
			case '|':
				block = new CDestructibleBlock(m_world, {((j+10) * widthmult), 825.0f - (i * heightmult)}, {30, 50}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
				m_allBlocks.push_back(block);
				break;
			case '=':
				block = new CDestructibleBlock(m_world, {(j+10) * widthmult, 825.0f - ((i * heightmult))}, {150, 15}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
				m_allBlocks.push_back(block);
				break;
			case 'O':
				block = new CDestructibleBlock(m_world, {(j+10) * widthmult, 825.0f - (i * heightmult)}, 40, b2_dynamicBody, "Block_Stone_Circle_1.png", CDestructibleBlock::BlockType::STONE);
				m_allBlocks.push_back(block);
				break;
			case 'P':
				pig = new CPig(m_world, {(j+10) * widthmult, 825.0f - (i * heightmult)}, 25, b2_dynamicBody, "Pig_Regular_1.png");
				m_allPigs.push_back(pig);
				break;
			case '{':
				block = new CDestructibleBlock(m_world, {((j+10) * widthmult) - 10.0f, 825.0f - (i * heightmult)}, {30, 50}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
				m_allBlocks.push_back(block);
				break;
			case '}':
				block = new CDestructibleBlock(m_world, {((j+10) * widthmult) + 10.0f, 825.0f - (i * heightmult)}, {30, 50}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
				m_allBlocks.push_back(block);
				break;
			case 'b':
				block = new CDestructibleBlock(m_world, {(j+10) * widthmult, 825.0f - (i * heightmult)}, {50, 50}, b2_dynamicBody, "Block_Wood_Regular_1.png", CDestructibleBlock::BlockType::WOOD);
				m_allBlocks.push_back(block);
				break;
			case 'l':
				block = new CDestructibleBlock(m_world, {((j+10) * widthmult), 825.0f - (i * heightmult)}, {30, 50}, b2_dynamicBody, "Block_Wood_Regular_1.png", CDestructibleBlock::BlockType::WOOD);
				m_allBlocks.push_back(block);
				break;
			case '_':
				block = new CDestructibleBlock(m_world, {(j+10) * widthmult, 825.0f - ((i * heightmult))}, {150, 15}, b2_dynamicBody, "Block_Wood_Regular_1.png", CDestructibleBlock::BlockType::WOOD);
				m_allBlocks.push_back(block);
				break;
			case 'o':
				block = new CDestructibleBlock(m_world, {(j+10) * widthmult, 825.0f - (i * heightmult)}, 40, b2_dynamicBody, "Block_Wood_Circle_1.png", CDestructibleBlock::BlockType::WOOD);
				m_allBlocks.push_back(block);
				break;
			case '[':
				block = new CDestructibleBlock(m_world, {((j+10) * widthmult) - 10.0f, 825.0f - (i * heightmult)}, {30, 50}, b2_dynamicBody, "Block_Wood_Regular_1.png", CDestructibleBlock::BlockType::WOOD);
				m_allBlocks.push_back(block);
				break;
			case ']':
				block = new CDestructibleBlock(m_world, {((j+10) * widthmult) + 10.0f, 825.0f - (i * heightmult)}, {30, 50}, b2_dynamicBody, "Block_Wood_Regular_1.png", CDestructibleBlock::BlockType::WOOD);
				m_allBlocks.push_back(block);
				break;

			default:
				break;
			}
		}
	}
}

/// <summary>
/// Initialises level when changing
/// <para>Author: Keane, Nerys</para>
/// </summary>
void CGame::Init()
{
	if (m_isInitialised)
		return;
	m_isInitialised = true;

	m_gameClock.restart();

	switch (m_currentLevel)
	{
	case Level::One: //Nerys
	{

		sf::Vector2f shootPos = {200, 200};

		CBird *bird2 = new CBird(m_world, {50, 35}, 25, b2_dynamicBody, "Bird_Regular_1.png", CBird::BirdType::Regular);
		m_allBirds.push_back(bird2);
		bird2->SetShootPos(shootPos);

		CBird *bird1 = new CBird(m_world, {100, 35}, 25, b2_dynamicBody, "Bird_Fast_1.png", CBird::BirdType::Fast);
		m_allBirds.push_back(bird1);
		bird1->SetShootPos(shootPos);

		

		

		CDestructibleBlock *anchor = new CDestructibleBlock(m_world, {900, 650}, {10, 10}, b2_staticBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
		m_allBlocks.push_back(anchor);
		CDestructibleBlock *rectBody = new CDestructibleBlock(m_world, {1100, 650}, {200, 10}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
		rectBody->GetBody()->GetFixtureList()[0].SetDensity(0.1f);
		rectBody->GetBody()->ResetMassData();
		m_allBlocks.push_back(rectBody);
		CDestructibleBlock *rectBody2 = new CDestructibleBlock(m_world, {1300, 650}, {200, 10}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
		rectBody2->GetBody()->GetFixtureList()[0].SetDensity(0.1f);
		rectBody2->GetBody()->ResetMassData();
		m_allBlocks.push_back(rectBody2);
		CDestructibleBlock *rectBody3 = new CDestructibleBlock(m_world, {1500, 650}, {200, 10}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
		rectBody3->GetBody()->GetFixtureList()[0].SetDensity(0.1f);
		rectBody3->GetBody()->ResetMassData();
		m_allBlocks.push_back(rectBody3);
		CDestructibleBlock *circleBody = new CDestructibleBlock(m_world, {1700, 650}, 40, b2_dynamicBody, "Block_Stone_Circle_1.png", CDestructibleBlock::BlockType::STONE);
		m_allBlocks.push_back(circleBody);
		
		char level[17][20] = { // The level in Text form, its much faster to design levels this way.
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ']', ' ', '['}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ']', ' ', '['}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ']', ' ', '['}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', ' '}, 
			{' ', ' ', ' ', ' ', 'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '[', ' ', ']'}, 
			{' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '[', ' ', ']'}, 
			{' ', ' ', ' ', '{', ' ', ']', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '[', ' ', ']'}, 
			{' ', ' ', ' ', '{', ' ', ']', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '[', ' ', ']'}, 
			{' ', ' ', ' ', '{', ' ', ']', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ', ' ', ' ', 'B', ' ', 'B'}, 
			{' ', ' ', ' ', '{', 'P', ']', ' ', ' ', ' ', ' ', ' ', 'P', ' ', 'l', ' ', ' ', ' ', 'B', ' ', 'B'}, 
			{' ', ' ', ' ', '{', 'l', ']', ' ', ' ', ' ', ' ', ' ', 'l', ' ', 'l', ' ', ' ', ' ', 'B', 'B', 'B'}};
		PlaceLevel(level);

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
		revoluteJointDef2.localAnchorA.Set(-100 / SCALE, 0 / SCALE);
		revoluteJointDef2.localAnchorB.Set(100 / SCALE, 0 / SCALE);
		m_world->CreateJoint(&revoluteJointDef2);

		b2RevoluteJointDef revoluteJointDef3;
		revoluteJointDef3.bodyA = rectBody2->GetBody();
		revoluteJointDef3.bodyB = rectBody3->GetBody();
		revoluteJointDef3.collideConnected = false;
		revoluteJointDef3.localAnchorA.Set(-100 / SCALE, 0 / SCALE);
		revoluteJointDef3.localAnchorB.Set(100 / SCALE, 0 / SCALE);
		m_world->CreateJoint(&revoluteJointDef3);

		b2WeldJointDef revoluteJointDef4;
		revoluteJointDef4.bodyA = rectBody3->GetBody();
		revoluteJointDef4.bodyB = circleBody->GetBody();
		revoluteJointDef4.collideConnected = false;
		revoluteJointDef4.localAnchorA.Set(-100 / SCALE, 0 / SCALE);
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

	case Level::Two: //Nerys
	{

		sf::Vector2f shootPos = {200, 200};

		CBird *bird2 = new CBird(m_world, {50, 35}, 25, b2_dynamicBody, "Bird_Dropper_1.png", CBird::BirdType::Dropper);
		m_allBirds.push_back(bird2);
		bird2->SetShootPos(shootPos);

		CBird *bird1 = new CBird(m_world, {100, 35}, 25, b2_dynamicBody, "Bird_Fast_1.png", CBird::BirdType::Fast);
		m_allBirds.push_back(bird1);
		bird1->SetShootPos(shootPos);

		

		

		CDestructibleBlock *anchor = new CDestructibleBlock(m_world, {750, 183}, {10, 10}, b2_staticBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
		m_allBlocks.push_back(anchor);
		CDestructibleBlock *rectBody = new CDestructibleBlock(m_world, {600, 183}, {200, 50}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
		m_allBlocks.push_back(rectBody);
		rectBody->GetBody()->SetGravityScale(15.0f);
		
		CDestructibleBlock *anchor2 = new CDestructibleBlock(m_world, {1200, 25}, {10, 10}, b2_staticBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
		m_allBlocks.push_back(anchor);
		CDestructibleBlock *rectBody2 = new CDestructibleBlock(m_world, {1300, 25}, {300, 30}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
		m_allBlocks.push_back(rectBody2);
		CDestructibleBlock *rectBody3 = new CDestructibleBlock(m_world, {1450, 25}, {20, 30}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
		m_allBlocks.push_back(rectBody3);
		CDestructibleBlock *rectBody4 = new CDestructibleBlock(m_world, {1500, 25}, {20, 30}, b2_dynamicBody, "Block_Stone_Regular_1.png", CDestructibleBlock::BlockType::STONE);
		m_allBlocks.push_back(rectBody4);
		
		
		
		char level[17][20] = { // The level in Text form, its much faster to design levels this way.
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', '{', 'B', 'P', 'P', 'B', '}', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '=', ' ', ' ', '=', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', 'B', ' ', ' ', ' ', ' ', ' ', 'B', ' ', ' ', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', 'B', 'P', ' ', ' ', ' ', ' ', 'B', ' ', ' ', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', 'B', ' ', ' ', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', '{', 'B', 'P', ' ', 'B', '}', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', 'l', ' ', ' ', '{', ' ', '{', ' ', '}', '{', ' ', '}', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', 'l', 'P', ' ', '{', ' ', '{', ' ', '}', '{', ' ', '}', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
			{' ', ' ', 'l', '|', ' ', '{', ' ', 'B', 'B', 'B', 'B', 'B', 'B', ' ', ' ', ' ', ' ', ' ', ' ', 'O'}};
		PlaceLevel(level);

		b2RevoluteJointDef revoluteJointDef1;
		revoluteJointDef1.bodyA = anchor->GetBody();
		revoluteJointDef1.bodyB = rectBody->GetBody();
		revoluteJointDef1.collideConnected = false;
		revoluteJointDef1.localAnchorA.Set(0, 0);
		revoluteJointDef1.localAnchorB.Set(100 / SCALE, 0 / SCALE);
		b2Joint* revJoint1 = m_world->CreateJoint(&revoluteJointDef1);

		b2RevoluteJointDef revoluteJointDef2;
		revoluteJointDef2.bodyA = anchor2->GetBody();
		revoluteJointDef2.bodyB = rectBody2->GetBody();
		revoluteJointDef2.collideConnected = false;
		revoluteJointDef2.localAnchorA.Set(0,0);
		revoluteJointDef2.localAnchorB.Set(-150 / SCALE, 0 / SCALE);
		b2Joint* revJoint2 = m_world->CreateJoint(&revoluteJointDef2);

		b2WeldJointDef weldJointDef1;
		weldJointDef1.bodyA = rectBody2->GetBody();
		weldJointDef1.bodyB = rectBody3->GetBody();
		weldJointDef1.collideConnected = false;
		weldJointDef1.localAnchorA.Set(0 / SCALE, 10 / SCALE);
		weldJointDef1.localAnchorB.Set(-50 / SCALE, -15 / SCALE);
		m_world->CreateJoint(&weldJointDef1);

		b2WeldJointDef weldJointDef2;
		weldJointDef2.bodyA = rectBody2->GetBody();
		weldJointDef2.bodyB = rectBody4->GetBody();
		weldJointDef2.collideConnected = false;
		weldJointDef2.localAnchorA.Set(0 / SCALE, 10 / SCALE);
		weldJointDef2.localAnchorB.Set(-150 / SCALE, -15 / SCALE);
		m_world->CreateJoint(&weldJointDef2);

		b2GearJointDef gearJointDef;
		gearJointDef.bodyA = rectBody->GetBody();
		gearJointDef.bodyB = rectBody2->GetBody();
		gearJointDef.joint1 = revJoint1;
		gearJointDef.joint2 = revJoint2;
		gearJointDef.ratio = -0.5f;
		m_world->CreateJoint(&gearJointDef);


		

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
		_body->GetBody()->GetFixtureList()->SetSensor(true);

		if (_body)
			_body->Destroy();
	};
	m_allBirds.clear();

	for (CPig *_body : m_allPigs)
	{
		_body->GetBody()->GetFixtureList()->SetSensor(true);

		if (_body)
			_body->Destroy();
	};
	m_allPigs.clear();

	for (CDestructibleBlock *_body : m_allBlocks)
	{
		_body->GetBody()->GetFixtureList()->SetSensor(true);

		if (_body)
			_body->Destroy();
	};
	m_allBlocks.clear();

	for (CBody *_body : m_allGround)
	{
		_body->GetBody()->GetFixtureList()->SetSensor(true);

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

	if (!m_currentShooter || m_currentShooter->GetState() != CBird::BirdState::Shooting)
		FindNewShooter();

	if (m_world)
		m_world->Step((float)timeStep, velocityIterations, positionIterations);


	static float waitTimer = 0.0f;

	//Check for win and lose conditions: Nerys
	if (m_allPigs.empty())
	{
		if (waitTimer >= 2.0f) {
			if (m_currentLevel == Level::One)
			{
				Clear();
				SetLevel(Level::Two);
				waitTimer = 0.0f;
			}
			else
			{
				Clear();
			}
		}
		else {
			waitTimer += (1.0f / 60.0f);
		}
	}
	else if (m_allBirds.empty()) //Nerys
	{
		if (waitTimer >= 5.0f) {
			Clear();
			SetLevel(m_currentLevel);
			waitTimer = 0.0f;
		}
		else {
			waitTimer += (1.0f / 60.0f);
		}
		
	}
	
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