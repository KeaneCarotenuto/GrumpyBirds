#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "CResourceManager.h"
#include "utility.h"
#include "CCollision.h"

struct CollisionData
{
	std::string ObjName;
	b2Vec2 Velocity;
	float ObjMass;
	b2Vec2 CollisionNormal;
};

class CBody
{
public:
	static std::vector<CBody*> GetAllBodies() { return m_allBodies; };
	static std::vector<CBody*> GetToDelete() { return m_toDelete; };
	static void TryDestroys();

	static void SetWindow(sf::RenderWindow* _wind) { m_window = _wind; };
	static sf::RenderWindow* GetWindow() { return m_window; };

	b2Body* GETBODY_TODELETE() { return  m_body; };

	//Rect Constructor
	CBody(b2World* _world, sf::Vector2f _position, sf::Vector2f _size, b2BodyType _type, std::string _imgName);
	CBody(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName);

	void Destroy();

	void Draw();

	virtual void FixedUpdate();

	virtual void OnCollisionEnter(CollisionData _data);

	std::string GetName() { return m_name; };

	b2Body* GetBody() { return m_body; };

protected:
	//DO NOT CALL THIS, use .Destroy() INSTEAD!
	virtual ~CBody();

	static sf::RenderWindow* m_window;
	static std::vector<CBody*> m_allBodies;
	static std::vector<CBody*> m_toDelete;

	std::string m_name;

	//SFML
	sf::Texture* m_texture;
	sf::Sprite* m_sprite;

	//BOX2D
	b2World* m_world;
	b2BodyDef* m_bodyDef;
	b2Body* m_body;
	b2Shape* m_shape;
	b2FixtureDef* m_fixture;
};

