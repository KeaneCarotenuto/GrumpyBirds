#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

#define SCALE (double)30.0

class CBody
{
private:
	static sf::RenderWindow* m_window;
	static std::vector<CBody*> m_allBodies;

	//SFML
	sf::Texture* m_texture;
	sf::Sprite* m_sprite;

	//BOX2D
	b2BodyDef* m_bodyDef;
	b2Body* m_body;
	b2Shape* m_shape;
	b2FixtureDef* m_fixture;

public:
	static std::vector<CBody*> GetAllBodies() { return m_allBodies; };

	static void SetWindow(sf::RenderWindow* _wind) { m_window = _wind; };
	static sf::RenderWindow* GetWindow() { return m_window; };

	//Rect Constructor
	CBody(b2World* _world, sf::Vector2f _position, sf::Vector2f _size, b2BodyType _type);
	CBody(b2World* _world, sf::Vector2f _position, float _radius, b2BodyType _type);
	~CBody();

	void Draw() { 
		//update visual
		b2Vec2 position = m_body->GetPosition();
		float angle = m_body->GetAngle();
		m_sprite->setPosition(position.x * 30.0, m_window->getSize().y - position.y * 30.0);
		m_sprite->setRotation(-angle / (M_PI / 180.0));

		m_window->draw(*m_sprite); 
	}
};

