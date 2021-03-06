// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2021 Media Design School
//
// File Name   : CBody.cpp
// Description : Body class
// Authors     : Keane Carotenuto
// Mail        : KeaneCarotenuto@gmail.com

#ifndef CBODY_H
#define CBODY_H

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "CResourceManager.h"
#include "utility.h"
#include "CCollision.h"

//forward
class CBody;

/// <summary>
/// Collision data to pass to collision methods
/// <para>Author: Nerys</para>
/// </summary>
struct CollisionData
{
	CBody *other;
	std::string ObjName;
	b2Vec2 Velocity;
	b2Vec2 VelocityDelta;
	b2Vec2 Momentum;
	float ObjMass;
	b2Vec2 CollisionNormal;
};

/// <summary>
/// Body class for all gameobjects. Manages things like sprites, rigid bodies, collisions, updates, drawing
/// <para>Author: Keane</para>
/// </summary>
class CBody
{
public:
	static std::vector<CBody *> GetAllBodies() { return m_allBodies; };
	static std::vector<CBody *> GetToDelete() { return m_toDelete; };
	static void TryDestroys();

	static void SetWindow(sf::RenderWindow *_wind) { m_window = _wind; };
	static sf::RenderWindow *GetWindow() { return m_window; };

	b2Body *GETBODY_TODELETE() { return m_body; };

	//Rect Constructor
	CBody(b2World *_world, sf::Vector2f _position, sf::Vector2f _size, b2BodyType _type, std::string _imgName);
	CBody(b2World *_world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName);

	void Destroy(double _delay = 0.0);
	bool IsDeleting() { return m_markedForDelete; };

	void Draw();

	virtual void FixedUpdate();

	virtual void OnCollisionEnter(CollisionData _data);

	std::string GetName() { return m_name; };

	b2Body *GetBody() { return m_body; };

protected:
	//DO NOT CALL THIS, use .Destroy() INSTEAD!
	virtual ~CBody();

	static sf::RenderWindow *m_window;
	static std::vector<CBody *> m_allBodies;
	static std::vector<CBody *> m_toDelete;

	std::string m_name;

	//SFML
	sf::Texture *m_texture;
	sf::Sprite *m_sprite;

	//BOX2D
	b2World *m_world;
	b2BodyDef *m_bodyDef;
	b2Body *m_body;
	b2Shape *m_shape;
	b2FixtureDef *m_fixture;

	bool m_markedForDelete = false;

	double m_deleteCallTime = 0.0;
	double m_deleteDelay = 0.0;
};

#endif
