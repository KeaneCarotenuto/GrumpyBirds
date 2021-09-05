#ifndef C_DESTRUCTIBLE_BLOCK_H
#define C_DESTRUCTIBLE_BLOCK_H
#include "CBody.h"
#include "utility.h"


class CDestructibleBlock : public CBody
{
public:

	CDestructibleBlock(b2World *_world, sf::Vector2f _position, sf::Vector2f _size, b2BodyType _type, std::string _imgName);
	CDestructibleBlock(b2World *_world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName);

	void Destroy();

	void FixedUpdate();

	void OnCollisionEnter(CollisionData _data);


protected:
	~CDestructibleBlock();
};

#endif 
