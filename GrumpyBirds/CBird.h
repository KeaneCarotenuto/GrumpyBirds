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

	void FixedUpdate();

	void OnCollisionEnter(CollisionData _data);

private:
	void DoWaiting();
	void DoMoving();
	void DoShooting();

	BirdType m_type = BirdType::Regular;
	BirdState m_state = BirdState::Waiting;

	sf::Vector2f m_shootPos = {100,100};

protected:
	~CBird();
};

