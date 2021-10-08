#include "CDestructibleBlock.h"
#include "CCollision.h"
#include "CBird.h"

CDestructibleBlock::CDestructibleBlock(b2World *_world, sf::Vector2f _position, sf::Vector2f _size, b2BodyType _type, std::string _imgName, BlockType _blockType) : CBody(_world, _position, _size, _type, _imgName)
{
    m_body->GetUserData().pointer = (uintptr_t)(this);
    m_type = _blockType;

    m_name = "BLOCK";
}

CDestructibleBlock::CDestructibleBlock(b2World *_world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName, BlockType _blockType) : CBody(_world, _position, _radius, _type, _imgName)
{
    m_body->GetUserData().pointer = (uintptr_t)(this);
    m_type = _blockType;

    m_name = "BLOCK";
}

void CDestructibleBlock::FixedUpdate()
{
}

void CDestructibleBlock::Destroy()
{
    std::cout << "Destroy block\n";

    CBody::Destroy();
}

void CDestructibleBlock::OnCollisionEnter(CollisionData _data)
{

    if ((_data.Momentum.Length() > 38.0f && m_type == BlockType::WOOD))
    {
        Destroy();
    }
}

CDestructibleBlock::~CDestructibleBlock()
{
    std::cout << "--Delete block\n";
}
