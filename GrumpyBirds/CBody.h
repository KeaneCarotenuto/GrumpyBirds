#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "CResourceManager.h"

#define SCALE (double)30.0

class CBody
{
private:
	//DO NOT CALL THIS, use .Destroy() INSTEAD!
	~CBody();

	static sf::RenderWindow* m_window;
	static std::vector<CBody*> m_allBodies;
	static std::vector<CBody*> m_toDelete;

	//SFML
	sf::Texture* m_texture;
	sf::Sprite* m_sprite;

	//BOX2D
	b2World* m_world;
	b2BodyDef* m_bodyDef;
	b2Body* m_body;
	b2Shape* m_shape;
	b2FixtureDef* m_fixture;

public:
	static std::vector<CBody*> GetAllBodies() { return m_allBodies; };
	static std::vector<CBody*> GetToDelete() { return m_toDelete; };
	static void TryDestroys();

	static void SetWindow(sf::RenderWindow* _wind) { m_window = _wind; };
	static sf::RenderWindow* GetWindow() { return m_window; };

	//Rect Constructor
	CBody(b2World* _world, sf::Vector2f _position, sf::Vector2f _size, b2BodyType _type, std::string _imgName);
	CBody(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type, std::string _imgName);

	void Destroy() { m_toDelete.push_back(this); };

	void Draw();
};
