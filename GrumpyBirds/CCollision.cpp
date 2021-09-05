#include "CCollision.h"

#include "CBird.h"

CCollision::CCollision()
{
}

CCollision::~CCollision()
{
}

void CCollision::BeginContact(b2Contact* _contact)
{
	auto bodyUserDataOne = (CBody*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto bodyUserDataTwo = (CBody*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (dynamic_cast<CBird*>(bodyUserDataOne)) {
		dynamic_cast<CBird*>(bodyUserDataOne)->Collision();
	}

	if (dynamic_cast<CBird*>(bodyUserDataTwo)) {
		dynamic_cast<CBird*>(bodyUserDataTwo)->Collision();
	}
}

void CCollision::EndContact(b2Contact* _contact)
{
}
