// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2021 Media Design School
//
// File Name   : CCollision.h
// Description : Collision class
// Authors     : Keane Carotenuto, Nerys Thamm
// Mail        : KeaneCarotenuto@gmail.com, nerysthamm@gmail.com

#ifndef CCOLLISION_H
#define CCOLLISION_H
#include "box2d/box2d.h"

/// <summary>
/// Basic collision class to get callbacks from box2d
/// <para>Author: Keane</para>
/// </summary>
class CCollision : public b2ContactListener
{
public:
	CCollision();
	~CCollision();

	void BeginContact(b2Contact* _contact);
	void EndContact(b2Contact* _contact);
};
#endif

