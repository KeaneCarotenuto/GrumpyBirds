// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2021 Media Design School
//
// File Name   : CBird.hpp
// Description : Bird Class
// Authors     : Keane Carotenuto
// Mail        : KeaneCarotenuto@gmail.com

#ifndef CBIRD_H
#define CBIRD_H
#include "CBody.h"
#include "utility.h"

/// <summary>
/// Bird class to manage shooting, collisions, and states
/// <para>Author: Keane</para>
/// </summary>
class CBird : public CBody
{
public:
	enum class BirdType
	{
		Regular,
		Fast,
		Bomb,
		Split,
		Expand,
		Dropper,
	};

	enum class BirdState
	{
		Waiting,	// Waiting to be loaded
		Shooting,	// Being aimed
		Moving,		// Has been shot and is moving through the air
		Destroying, // Has hit something and is waiting to be destroyed
	};

	CBird(b2World *_world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName, BirdType _birdType);

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

	void PullBack();

	void TryShoot();

	b2Vec2 CalcShootVel();

	BirdType m_type = BirdType::Regular;
	BirdState m_state = BirdState::Waiting;

	sf::Vector2f m_shootPos = {0, 0};
	float m_pullBackDist = 100.0f;
	float m_shootMulti = 10.0f;
	float m_maxShootSpeed = 30.0f;

	bool m_mouseHolding = false;
	bool m_mouseDown = false;
	bool m_releasedThisFrame = false;

	bool m_hasUsedAbility = false;
	float m_autoDestroyTimer = 3.0f;

protected:
	~CBird();
};
#endif
