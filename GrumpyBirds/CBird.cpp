#include "CBird.h"

#include"CCollision.h"

CBird::CBird(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName) : 
	CBody(_world, _position, _radius, _type, _imgName)
{

	m_body->GetUserData().pointer = (uintptr_t)(this);
}

void CBird::Destroy()
{
    std::cout << "Destroy bird\n";

	CBody::Destroy();
}

void CBird::FixedUpdate()
{

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
	std::cout << "Bird Col\n";
	std::cout << "- x:" << _data.Velocity.x << ", y:" << _data.Velocity.y << "\n";
}

void CBird::DoMoving()
{
	//std::cout << "Do Moving\n";
}

void CBird::DoShooting()
{
	//std::cout << "Do Shooting\n";
}

void CBird::DoWaiting()
{
	//std::cout << "Do Waiting\n";
}

CBird::~CBird()
{
	std::cout << "Delete bird\n";
}
