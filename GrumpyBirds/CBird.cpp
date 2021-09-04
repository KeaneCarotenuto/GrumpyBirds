#include "CBird.h"

CBird::CBird(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName) : 
	CBody(_world, _position, _radius, _type, _imgName)
{

}

void CBird::Destroy()
{
	CBody::Destroy();
}

CBird::~CBird()
{
}
