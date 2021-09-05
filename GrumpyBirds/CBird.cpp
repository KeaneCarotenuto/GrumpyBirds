#include "CBird.h"

#include"CCollision.h"

CBird::CBird(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName) : 
	CBody(_world, _position, _radius, _type, _imgName)
{

	m_body->GetUserData().pointer = (uintptr_t)(this);

	SetState(BirdState::Waiting);
	m_name = "BIRD";
}

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

void CBird::Destroy()
{
    std::cout << "Destroy bird\n";

	CBody::Destroy();
}

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

	default:
		break;
	}
}

void CBird::OnCollisionEnter(CollisionData _data)
{
	if (_data.other->GetBody()->GetFixtureList()->IsSensor()) return;

	std::cout << "Bird col\n";
}

void CBird::DoMoving()
{
	//std::cout << "Do Moving\n";
}

void CBird::DoShooting()
{
	//std::cout << "Do Shooting\n";


	//get mouse pos
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	//if mouse is pressed, try grab
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		
		//if the mouse is being pressed this frame
		if (!m_mouseDown) {
			m_mouseDown = true;

			//If not holding a bird, check if the mouse intersects the main bird.
			if (!m_mouseHolding && m_sprite->getGlobalBounds().contains(mousePos)) {
				//if so, start trying holding bird
				m_mouseHolding = true;
			}
		}
	}
	else {
		m_mouseDown = false;
		if (m_mouseHolding) {
			releasedThisFrame = true;
		}
		m_mouseHolding = false;
	}

	if (m_mouseHolding) {
		//If holding on bird, try grab it
		PullBack();
	}
	else {
		//if mouse was let go this frame, try shoot the bird
		if (releasedThisFrame) {
			TryShoot();
		}
		else {
			//otherwise, set the bird pos back to the shootpos
			m_body->SetTransform(util::V(m_shootPos), m_body->GetAngle());
		}
	}
}

/// <summary>
/// Attempt to pull back the bird
/// </summary>
void CBird::PullBack()
{
	//get mouse pos, then get pos in world
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*m_window));
	sf::Vector2f mouseWorldPos = util::V(util::ScreenToWorld(mousePos));

	//calc desired aim vec
	sf::Vector2f aimVector = (m_shootPos - mouseWorldPos);

	//If aim vec is too far, cap it at max distance
	if (util::Mag(aimVector) >= m_pullBackDist) {
		aimVector = util::Normalize(aimVector) * m_pullBackDist;
	}

	//set bird to pos of aim vec
	m_body->SetTransform(util::V(m_shootPos - aimVector), m_body->GetAngle());
}

/// <summary>
/// Attempt to shoot the bird from the current pos
/// </summary>
void CBird::TryShoot()
{
	SetState(BirdState::Moving);
	b2Vec2 newVel = m_shootMulti * (util::V(m_shootPos) - m_body->GetPosition());

	if (util::Mag(newVel) >= m_maxShootSpeed) {
		newVel = m_maxShootSpeed * util::Normalize(newVel);
	}

	m_body->SetLinearVelocity(newVel);
	std::cout << "\nShoot Vel: " << m_body->GetLinearVelocity().Length() << "\n\n";
}

void CBird::DoWaiting()
{
	//std::cout << "Do Waiting\n";
}

CBird::~CBird()
{
	std::cout << "--Delete bird\n";
}
