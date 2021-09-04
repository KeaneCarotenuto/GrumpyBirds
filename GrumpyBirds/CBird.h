#pragma once
#include "CBody.h"
#include "utility.h"

class CBird : public CBody
{
public:
	enum class BirdType {
		Regular,
		Fast,
		Bomb,
		Split,
		Expand,
		Dropper,
	};

	enum class BirdState {
		Waiting,
		Shooting,
		Moving
	};

	CBird(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName);

	void Destroy();

private:
	~CBird();

	BirdType m_type = BirdType::Regular;
	BirdState m_state = BirdState::Moving;

	b2Vec2 m_shootPos;
};

