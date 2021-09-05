#ifndef CCOLLISION_H
#define CCOLLISION_H
#include "box2d/box2d.h"

class CCollision : public b2ContactListener
{
public:
	CCollision();
	~CCollision();

	void BeginContact(b2Contact* _contact);
	void EndContact(b2Contact* _contact);
};
#endif

