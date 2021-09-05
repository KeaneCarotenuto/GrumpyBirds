#include "CDestructibleBlock.h"
#include"CCollision.h"

CDestructibleBlock::CDestructibleBlock(b2World *_world, sf::Vector2f _position, sf::Vector2f _size, b2BodyType _type, std::string _imgName) : 
CBody(_world, _position, _size, _type, _imgName)
{
    m_body->GetUserData().pointer = (uintptr_t)(this);
}

CDestructibleBlock::CDestructibleBlock(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName) :
    CBody(_world, _position, _radius, _type, _imgName)
{
    m_body->GetUserData().pointer = (uintptr_t)(this);
}



void CDestructibleBlock::FixedUpdate() {
    
}

void CDestructibleBlock::Destroy() {
    std::cout << "Destroy block\n";

    CBody::Destroy();
}

void CDestructibleBlock::OnCollisionEnter(CollisionData _data) {
    std::cout << "Block col\n";

    if (_data.ObjName == "BIRD")
    {
        Destroy();
    }
    
}

CDestructibleBlock::~CDestructibleBlock() {
    std::cout << "--Delete block\n";
}

