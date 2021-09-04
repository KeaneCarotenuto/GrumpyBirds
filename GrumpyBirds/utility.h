#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

#define SCALE (float)30.0f

namespace util {
	extern sf::RenderWindow* window;

	static b2Vec2 V(sf::Vector2f _a) {
		return { _a.x / SCALE, _a.y / SCALE };
	}

	static sf::Vector2f V(b2Vec2 _a) {
		return { _a.x * SCALE, _a.y * SCALE };
	}

	static sf::Vector2f WorldToScreen(b2Vec2 _a) {
		return { _a.x * SCALE, window->getSize().y - _a.y * SCALE };
	}

	static b2Vec2 ScreenToWorld(sf::Vector2f _a) {
		return { _a.x / SCALE, (window->getSize().y - _a.y) / SCALE };
	}

	static float Degrees(float _rad) {
		return _rad * (180.0 / M_PI);
	}

	static float Radians(float _deg) {
		return _deg / (180.0 / M_PI);
	}
}