#include "CBird.h"

#include"CCollision.h"

CBird::CBird(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName) : 
	CBody(_world, _position, _radius, _type, _imgName)
{

	m_body->GetUserData().pointer = (uintptr_t)(this);

	SetState(BirdState::Waiting);
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

	std::cout << "Bird Col\n";
}

void CBird::DoMoving()
{
	//std::cout << "Do Moving\n";
}

void CBird::DoShooting()
{
	//std::cout << "Do Shooting\n";

	bool releasedThisFrame = false;

	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

		if (!m_mouseDown) {
			m_mouseDown = true;

			if (!m_mouseHolding && m_sprite->getGlobalBounds().contains(mousePos)) {
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
		sf::Vector2f newPos = util::V(util::ScreenToWorld(mousePos));
		sf::Vector2f shootVector = (m_shootPos - newPos);

		if (util::Mag(shootVector) >= m_pullBackDist) {
			shootVector = util::Normalize(shootVector) * m_pullBackDist;
		}
		m_body->SetTransform(util::V(m_shootPos - shootVector), m_body->GetAngle());
	}
	else {
		if (releasedThisFrame) {
			SetState(BirdState::Moving);
			b2Vec2 newVel = m_shootMulti * (util::V(m_shootPos) - m_body->GetPosition());

			m_body->SetLinearVelocity(newVel);
			std::cout << "Vel: " << m_body->GetLinearVelocity().Length() << "\n";
		}
		else {
			m_body->SetTransform(util::V(m_shootPos), m_body->GetAngle());
		}
		
	}
}

void CBird::DoWaiting()
{
	//std::cout << "Do Waiting\n";
}

CBird::~CBird()
{
	std::cout << "Delete bird\n";
}
