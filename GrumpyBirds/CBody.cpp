#include "CBody.h"
#include "CBird.h"

sf::RenderWindow* CBody::m_window;
std::vector<CBody*> CBody::m_allBodies;
std::vector<CBody*> CBody::m_toDelete;

void CBody::TryDestroys()
{
    std::vector<CBody*> failedDelete;
    failedDelete.clear();

    for (CBody* _body : m_toDelete) {
        if (!_body->m_world->IsLocked()) {
            std::vector<CBody*>::iterator it = std::find(m_allBodies.begin(), m_allBodies.end(), _body);
            if (it != m_allBodies.end()) {
                m_allBodies.erase(it);
            }

            delete _body;
        }
        else {
            failedDelete.push_back(_body);
        }
    }

    m_toDelete = failedDelete;
}

CBody::CBody(b2World* _world, sf::Vector2f _position, sf::Vector2f _size, b2BodyType _type, std::string _imgName)
{
    m_world = _world;

	m_sprite = new sf::Sprite();
    (m_sprite)->setPosition(_position);
    m_texture = new sf::Texture();
    if (!m_texture->loadFromImage(*CResourceManager::GetImage(_imgName))) {
        std::cerr << "\nWARNING: <CBody::CBody> [_img] does not exist.\n";
    }
    (m_sprite)->setTexture(*m_texture);
    (m_sprite)->setOrigin(m_sprite->getGlobalBounds().width / 2, m_sprite->getGlobalBounds().height / 2);
    (m_sprite)->setScale(_size.x / 100, _size.y / 100);
    

    m_bodyDef =  new b2BodyDef();
    m_bodyDef->position = util::V(_position);
    m_bodyDef->type = _type;
    m_body = m_world->CreateBody(m_bodyDef);

    m_shape = new b2PolygonShape();
    dynamic_cast<b2PolygonShape*>(m_shape)->SetAsBox((_size.x / 2) / SCALE, (_size.y / 2) / SCALE);
    m_fixture = new b2FixtureDef();
    m_fixture->density = 1.f;
    m_fixture->shape = m_shape;
    m_body->CreateFixture(m_fixture);

    m_body->GetUserData().pointer = (uintptr_t)(this);

    m_allBodies.push_back(this);
}

CBody::CBody(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName)
{
    m_world = _world;

    m_sprite = new sf::Sprite();
    (m_sprite)->setPosition(_position);
    m_texture = new sf::Texture();
    if (!m_texture->loadFromImage(*CResourceManager::GetImage(_imgName))) {
        std::cerr << "\nWARNING: <CBody::CBody> [_img] does not exist.\n";
    }
    (m_sprite)->setTexture(*m_texture);
    (m_sprite)->setOrigin(m_sprite->getGlobalBounds().width / 2, m_sprite->getGlobalBounds().height / 2);
    (m_sprite)->setScale(_radius * 2 / 100, _radius * 2 / 100);


    m_bodyDef = new b2BodyDef();
    m_bodyDef->position = util::V(_position);
    m_bodyDef->type = _type;
    m_body = _world->CreateBody(m_bodyDef);

    m_shape = new b2CircleShape();
    dynamic_cast<b2CircleShape*>(m_shape)->m_radius = _radius / SCALE;
    m_fixture = new b2FixtureDef();
    m_fixture->density = 1.f;
    m_fixture->shape = m_shape;
    m_body->CreateFixture(m_fixture);

    m_body->GetUserData().pointer = (uintptr_t)(this);

    m_allBodies.push_back(this);
}

void CBody::Destroy()
{
    std::cout << "-Destroy body\n";

    std::vector<CBody*>::iterator it = std::find(m_toDelete.begin(), m_toDelete.end(), this);
    if (it == m_toDelete.end()) {
        m_toDelete.push_back(this);
    }
    else {
        //Already in list
    }
}

void CBody::Draw()
{
    //update visual
    m_sprite->setPosition(util::WorldToScreen(m_body->GetPosition()));
    m_sprite->setRotation(-util::Degrees(m_body->GetAngle()));

    m_window->draw(*m_sprite);
}

void CBody::FixedUpdate()
{
}

void CBody::OnCollisionEnter(CollisionData _data)
{
    std::cout << "Body Col\n";
}

CBody::~CBody()
{
    std::cout << "-Delete Body\n";

    std::vector<CBody*>::iterator it = std::find(m_allBodies.begin(), m_allBodies.end(), this);
    if (it != m_allBodies.end()) {
        m_allBodies.erase(it);
    }
    else {
        //doesnt exit in m_bodies anymore
    }

    //SFML
    delete m_texture;
    delete m_sprite;

    //BOX2D
    m_body->DestroyFixture(m_body->GetFixtureList());
    if (m_body) m_world->DestroyBody(m_body);
    if (m_bodyDef)delete m_bodyDef;
    delete m_shape;
    delete m_fixture;

    m_world = nullptr;
}