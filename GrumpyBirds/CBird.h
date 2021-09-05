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
		Moving,
		//OffScreen
	};

	CBird(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName);

	void SetState(BirdState _state);
	BirdState GetState() { return m_state; };

	void SetShootPos(sf::Vector2f _pos) { m_shootPos = _pos; };

	void Destroy();

	void FixedUpdate();
	void OnCollisionEnter(CollisionData _data);

private:
	void DoWaiting();
	void DoMoving();
	void DoShooting();

	BirdType m_type = BirdType::Regular;
	BirdState m_state = BirdState::Waiting;

	sf::Vector2f m_shootPos = {0,0};
	float m_pullBackDist = 100.0f;
	float m_shootMulti = 10.0f;
	float m_maxShootSpeed = 10.0f;

	bool m_mouseHolding = false;
	bool m_mouseDown = false;

protected:
	~CBird();
};

