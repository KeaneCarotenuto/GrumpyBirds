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

    if (bodyUserDataOne && bodyUserDataTwo)
    {
        CBody* CBodyA = bodyUserDataOne;
        CBody* CBodyB = bodyUserDataTwo;

        b2Body* bodyA = CBodyA->GetBody();
        b2Body* bodyB = CBodyB->GetBody();

        CollisionData aData, bData;
        aData.ObjName = CBodyA->GetName();
        bData.ObjName = CBodyB->GetName();

        aData.CollisionNormal = (bodyA->GetPosition() - bodyB->GetPosition());
        aData.CollisionNormal.Normalize();
        bData.CollisionNormal = (bodyB->GetPosition() - bodyA->GetPosition());
        bData.CollisionNormal.Normalize();

        aData.Velocity = bodyA->GetLinearVelocity();
        bData.Velocity = bodyB->GetLinearVelocity();

        aData.ObjMass = bodyA->GetMass();
        bData.ObjMass = bodyB->GetMass();

        CBodyA->OnCollisionEnter(bData);
        CBodyB->OnCollisionEnter(aData);
    }

	/*if (dynamic_cast<CBird*>(bodyUserDataOne)) {
		dynamic_cast<CBird*>(bodyUserDataOne)->Collision();
	}

	if (dynamic_cast<CBird*>(bodyUserDataTwo)) {
		dynamic_cast<CBird*>(bodyUserDataTwo)->Collision();
	}*/
}

void CCollision::EndContact(b2Contact* _contact)
{
}
