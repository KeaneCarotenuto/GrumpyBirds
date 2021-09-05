#include "CCollision.h"
#include "CBird.h"
#include "CDestructibleBlock.h"

CCollision::CCollision()
{
}

CCollision::~CCollision()
{
}

/// <summary>
/// Callback from box2D for collisions
/// <para>Primary Author: Nerys</para>
/// <para>Secondary Author: Keane (only about 6 lines)</para>
/// </summary>
/// <param name="_contact"></param>
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

        aData.other = CBodyA;
        bData.other = CBodyB;

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
}

void CCollision::EndContact(b2Contact* _contact)
{
}
