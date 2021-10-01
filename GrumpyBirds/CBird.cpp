#include "CBird.h"

#include "CCollision.h"
#include "CDestructibleBlock.h"
#include "CGame.h"

/// <summary>
/// Basic Bird Constructor
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_world"></param>
/// <param name="_position"></param>
/// <param name="_radius"></param>
/// <param name="_type"></param>
/// <param name="_imgName"></param>
CBird::CBird(b2World *_world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName, BirdType _birdType) : CBody(_world, _position, _radius, _type, _imgName)
{

	m_body->GetUserData().pointer = (uintptr_t)(this);

	SetState(BirdState::Waiting);
	m_name = "BIRD";
	m_type = _birdType;
}

/// <summary>
/// Set setate of bird to change how it behaves
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_state"></param>
void CBird::SetState(BirdState _state)
{
	m_state = _state;

	switch (m_state)
	{
	case CBird::BirdState::Waiting:
		m_body->SetType(b2BodyType::b2_staticBody);
		m_body->GetFixtureList()->SetSensor(true);
		break;

	case CBird::BirdState::Shooting:
		m_body->SetType(b2BodyType::b2_kinematicBody);
		m_body->GetFixtureList()->SetSensor(true);
		break;

	case CBird::BirdState::Moving:
		m_body->SetType(b2BodyType::b2_dynamicBody);
		m_body->GetFixtureList()->SetSensor(false);
		break;

		/*case CBird::BirdState::OffScreen:
		m_body->SetType(b2BodyType::b2_staticBody);
		m_body->GetFixtureList()->SetSensor(true);
		break;*/

	default:
		break;
	}
}

/// <summary>
/// Call this instead of delete, to safely delete
/// <para>Author: Keane</para>
/// </summary>
void CBird::Destroy()
{
	std::cout << "Destroy bird\n";

	CBody::Destroy();
}

/// <summary>
/// Fixed update for bird
/// <para>Author: Keane</para>
/// </summary>
void CBird::FixedUpdate()
{
	sf::Vector2f screenPos = util::WorldToScreen(m_body->GetPosition());

	/*if (m_state != BirdState::OffScreen &&
		(screenPos.x < 0 || screenPos.x > m_window->getSize().x ||
		screenPos.y < 0 || screenPos.y > m_window->getSize().y)) {
		SetState(BirdState::OffScreen);
		m_body->SetTransform();
	}*/

	switch (m_state)
	{
	case CBird::BirdState::Waiting:
		DoWaiting();
		break;

	case CBird::BirdState::Shooting:
		DoShooting();
		break;

	case CBird::BirdState::Moving:
		DoMoving();
		break;
	case CBird::BirdState::Destroying:
		if (m_autoDestroyTimer > 0.0f)
		{
			m_autoDestroyTimer -= (1.0f / 60.0f);
		}
		else
			Destroy();

	default:
		break;
	}
}

/// <summary>
/// Collisions for bird
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_data"></param>
void CBird::OnCollisionEnter(CollisionData _data)
{
	if (m_state == CBird::BirdState::Moving)
	{
		SetState(CBird::BirdState::Destroying);
	}
	if (_data.other->GetBody()->GetFixtureList()->IsSensor())
		return;

	std::cout << "Bird col\n";
}

/// <summary>
/// Code to execute while in moving state
/// <para>Author: Keane, Nerys</para>
/// </summary>
void CBird::DoMoving()
{
	//std::cout << "Do Moving\n";
	//--Nerys-----------------------------------------------------------------------------------------------------------
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !m_hasUsedAbility && m_state == CBird::BirdState::Moving) //Check for mouse press and valid states
	{
		b2Vec2 vel;
		m_hasUsedAbility = true;
		switch (m_type) //Do behaviour based on bird type
		{
		case CBird::BirdType::Fast:
			//Workaround to multiply the velocity vector by two because box2d vectors cant use the * operator

			vel.x = m_body->GetLinearVelocity().x * 2.0f;
			vel.y = m_body->GetLinearVelocity().y * 2.0f;
			m_body->SetLinearVelocity(vel);
			break;

		default:
			//If behaviour has not been coded yet or there is no behaviour for this bird
			break;
		}
	}
	//--------------------------------------------------------------------------------------------------------------------
}

/// <summary>
/// Code to execute while in shooting state
/// <para>Author: Keane</para>
/// </summary>
void CBird::DoShooting()
{
	//std::cout << "Do Shooting\n";

	//get mouse pos
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	//if mouse is pressed, try grab
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{

		//if the mouse is being pressed this frame
		if (!m_mouseDown)
		{
			m_mouseDown = true;

			//If not holding a bird, check if the mouse intersects the main bird.
			if (!m_mouseHolding && m_sprite->getGlobalBounds().contains(mousePos))
			{
				//if so, start trying holding bird
				m_mouseHolding = true;
			}
		}
	}
	else
	{
		m_mouseDown = false;
		if (m_mouseHolding)
		{
			m_releasedThisFrame = true;
		}
		m_mouseHolding = false;
	}

	if (m_mouseHolding)
	{
		//If holding on bird, try grab it
		PullBack();
	}
	else
	{
		//if mouse was let go this frame, try shoot the bird
		if (m_releasedThisFrame)
		{
			TryShoot();
		}
		else
		{
			//otherwise, set the bird pos back to the shootpos
			m_body->SetTransform(util::V(m_shootPos), m_body->GetAngle());
		}
	}
}

/// <summary>
/// Attempt to pull back the bird
/// <para>Author: Keane</para>
/// </summary>
void CBird::PullBack()
{
	//get mouse pos, then get pos in world
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*m_window));
	sf::Vector2f mouseWorldPos = util::V(util::ScreenToWorld(mousePos));

	//calc desired aim vec
	sf::Vector2f aimVector = (m_shootPos - mouseWorldPos);

	//If aim vec is too far, cap it at max distance
	if (util::Mag(aimVector) >= m_pullBackDist)
	{
		aimVector = util::Normalize(aimVector) * m_pullBackDist;
	}

	//set bird to pos of aim vec
	m_body->SetTransform(util::V(m_shootPos - aimVector), m_body->GetAngle());

	sf::Vector2f shootVel = util::V(CalcShootVel());

	//The "distance" that the dots will display in seconds
	float dotTime = 0.75f;

	//Caluclate the aim dots
	for (int i = 0; i < 20; i++)
	{
		float h = util::V(GetBody()->GetPosition()).y;
		float r = util::V(GetBody()->GetPosition()).x;
		float vy = shootVel.y;
		float vx = shootVel.x;
		float t = dotTime * (i / 20.0f);
		float g = -util::V(m_world->GetGravity()).y;

		sf::Vector2f pos(vx * t + r, h + vy * t - g * ((pow(t, 2.0f)) / (2.0f)));

		sf::CircleShape *circ = new sf::CircleShape((1.0f - t / dotTime) * 5);
		circ->setPosition(util::WorldToScreen(pos));
		circ->setOrigin(circ->getLocalBounds().width / 2.0f, circ->getLocalBounds().height / 2.0f);
		CGame::GetInstance()->DrawTempItem(circ);
		circ = nullptr;
	}
}

/// <summary>
/// Attempt to shoot the bird from the current pos
/// <para>Author: Keane</para>
/// </summary>
void CBird::TryShoot()
{
	SetState(BirdState::Moving);
	b2Vec2 newVel = CalcShootVel();

	m_body->SetLinearVelocity(newVel);
	std::cout << "\nShoot Vel: " << m_body->GetLinearVelocity().Length() << "\n\n";
}

/// <summary>
/// Calculates the shoot velocity based on relative position to slingshot
/// <para>Author: Keane</para>
/// </summary>
b2Vec2 CBird::CalcShootVel()
{
	b2Vec2 vel = m_shootMulti * (util::V(m_shootPos) - m_body->GetPosition());

	if (util::Mag(vel) >= m_maxShootSpeed)
	{
		vel = m_maxShootSpeed * util::Normalize(vel);
	}

	return vel;
}

/// <summary>
/// Code to execute while in waiting state
/// <para>Author: Keane</para>
/// </summary>
void CBird::DoWaiting()
{
	//std::cout << "Do Waiting\n";
}

/// <summary>
/// DO NOT CALL, use .Destroy() instead
/// <para>Author: Keane</para>
/// </summary>
CBird::~CBird()
{
	std::cout << "--Delete bird\n";
}
