#include "CBird.h"

CBird::CBird(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName) : 
	CBody(_world, _position, _radius, _type, _imgName)
{

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

void CBird::DoMoving()
{
	std::cout << "Do Moving\n";
}

void CBird::DoShooting()
{
	std::cout << "Do Shooting\n";
}

void CBird::DoWaiting()
{
	std::cout << "Do Waiting\n";
}

CBird::~CBird()
{
	std::cout << "Delete bird\n";
}
