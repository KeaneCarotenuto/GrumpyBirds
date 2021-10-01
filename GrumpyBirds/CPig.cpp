#include "CPig.h"
#include"CCollision.h"

CPig::CPig(b2World *_world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName) : 
CBody(_world, _position, _radius, _type, _imgName)
{
    m_body->GetUserData().pointer = (uintptr_t)(this);
}



void CPig::FixedUpdate() {
    
}

void CPig::Destroy() {
    std::cout << "Destroy pig\n";

    CBody::Destroy();
}

void CPig::OnCollisionEnter(CollisionData _data) {
    std::cout << "Pig col\n";

    if (_data.Momentum.Length() > 10.0f)
    {
        Destroy();
    }
    
}

CPig::~CPig() {
    std::cout << "--Delete pig\n";
}