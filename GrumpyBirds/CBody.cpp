#include "CBody.h"

sf::RenderWindow* CBody::m_window;
std::vector<CBody*> CBody::m_allBodies;

CBody::CBody(b2World* _world, sf::Vector2f _position, sf::Vector2f _size, b2BodyType _type)
{
	m_sprite = new sf::Sprite();
    (m_sprite)->setPosition(_position);
    m_texture = new sf::Texture();
    if (!m_texture->loadFromFile("Resources/Bird.png", sf::IntRect(0, 0, 100, 100))) {

    }
    (m_sprite)->setTexture(*m_texture);
    (m_sprite)->setOrigin(m_sprite->getGlobalBounds().width / 2, m_sprite->getGlobalBounds().height / 2);
    (m_sprite)->setScale(_size.x / 100, _size.y / 100);
    

    m_bodyDef =  new b2BodyDef();
    m_bodyDef->position = b2Vec2(_position.x / SCALE, _position.y / SCALE);
    m_bodyDef->type = _type;
    m_body = _world->CreateBody(m_bodyDef);

    m_shape = new b2PolygonShape();
    m_shape->SetAsBox((_size.x / 2) / SCALE, (_size.y / 2) / SCALE);
    m_fixture = new b2FixtureDef();
    m_fixture->density = 1.f;
    m_fixture->shape = m_shape;
    m_body->CreateFixture(m_fixture);

    m_allBodies.push_back(this);
}

CBody::~CBody()
{
    std::vector<CBody*>::iterator it = std::find(GetAllBodies().begin(), GetAllBodies().end(), this);
    if (it != GetAllBodies().end()) {
        m_allBodies.erase(it);
    }
    else {
        std::cerr << "\nWARNING: <CBody::~CBody> [this] does not exist in [m_allBodies]\n";
    }
}