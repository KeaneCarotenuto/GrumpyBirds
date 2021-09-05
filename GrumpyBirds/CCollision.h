#pragma once
#include "box2d/box2d.h"

class CCollision : public b2ContactListener
{
public:
	CCollision();
	~CCollision();

	void BeginContact(b2Contact* _contact);
	void EndContact(b2Contact* _contact);
};

