#include "CBody.h"
#include "CBird.h"
#include "CGame.h"

sf::RenderWindow* CBody::m_window;
std::vector<CBody*> CBody::m_allBodies;
std::vector<CBody*> CBody::m_toDelete;

/// <summary>
/// Destroy any objects that need to be destroyed
/// <para>Author: Keane</para>
/// </summary>
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

/// <summary>
/// Constructor for rectangle body
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_world"> box2d world it will be in</param>
/// <param name="_position"> spawn position</param>
/// <param name="_size"> width and height</param>
/// <param name="_type"> body type</param>
/// <param name="_imgName"> sprite name</param>
CBody::CBody(b2World* _world, sf::Vector2f _position, sf::Vector2f _size, b2BodyType _type, std::string _imgName)
{
    m_world = _world;

	m_sprite = new sf::Sprite();
    (m_sprite)->setPosition(_position);
    m_texture = new sf::Texture();

    sf::Vector2f imgSize = { 0,0 };

    if (!m_texture->loadFromImage(*CResourceManager::GetImage(_imgName))) {
        std::cerr << "\nWARNING: <CBody::CBody> [_img] does not exist.\n";
    }
    imgSize = (sf::Vector2f)CResourceManager::GetImage(_imgName)->getSize();
    (m_sprite)->setTexture(*m_texture);
    (m_sprite)->setOrigin(m_sprite->getGlobalBounds().width / 2, m_sprite->getGlobalBounds().height / 2);
    (m_sprite)->setScale(_size.x / imgSize.x, _size.y / imgSize.y);
    

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

/// <summary>
/// Constructor for circle body
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_world"> box2d world it will be in</param>
/// <param name="_position"> spawn position</param>
/// <param name="_size"> width and height</param>
/// <param name="_type"> body type</param>
/// <param name="_imgName"> sprite name</param>
CBody::CBody(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName)
{
    m_world = _world;

    m_sprite = new sf::Sprite();
    (m_sprite)->setPosition(_position);
    m_texture = new sf::Texture();
    sf::Vector2f imgSize = { 0,0 };
    if (!m_texture->loadFromImage(*CResourceManager::GetImage(_imgName))) {
        std::cerr << "\nWARNING: <CBody::CBody> [_img] does not exist.\n";
    }
    imgSize = (sf::Vector2f)CResourceManager::GetImage(_imgName)->getSize();
    (m_sprite)->setTexture(*m_texture);
    (m_sprite)->setOrigin(m_sprite->getGlobalBounds().width / 2, m_sprite->getGlobalBounds().height / 2);
    (m_sprite)->setScale(_radius * 2 / imgSize.x, _radius * 2 / imgSize.y);


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

/// <summary>
/// Use this instead of delete
/// <para>Author: Keane</para>
/// </summary>
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

/// <summary>
/// Draws sprite using body transform
/// <para>Author: Keane</para>
/// </summary>
void CBody::Draw()
{
    //update visual
    m_sprite->setPosition(util::WorldToScreen(m_body->GetPosition()));
    m_sprite->setRotation(-util::Degrees(m_body->GetAngle()));

    m_window->draw(*m_sprite);
}

/// <summary>
/// Virtual fixed update
/// <para>Author: Keane</para>
/// </summary>
void CBody::FixedUpdate()
{
}

/// <summary>
/// Virtual collision call
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_data"></param>
void CBody::OnCollisionEnter(CollisionData _data)
{
    std::cout << "Body col\n";
}

/// <summary>
/// DO NOT CALL, use .Destroy() instead
/// <para>Author: Keane</para>
/// </summary>
CBody::~CBody()
{
    std::cout << "---Delete Body\n\n";

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