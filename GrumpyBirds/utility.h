// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2021 Media Design School
//
// File Name   : utility.h
// Description : Utility file to keep useful functions
// Authors     : Keane Carotenuto
// Mail        : KeaneCarotenuto@gmail.com

#ifndef UTILITY_H
#define UTILITY_H
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include <chrono>
#include <iostream>

#define SCALE (float)30.0f

/// <summary>
/// Utility namepsace for commonly used functions
/// <para>Author: Keane</para>
/// </summary>
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

	static sf::Vector2f WorldToScreen(sf::Vector2f _a) {
		return { _a.x, window->getSize().y - _a.y };
	}

	static b2Vec2 ScreenToWorld(sf::Vector2f _a) {
		return { _a.x / SCALE, (window->getSize().y - _a.y) / SCALE };
	}

	static float Degrees(float _rad) {
		return _rad * (180.0f / (float)M_PI);
	}

	static float Radians(float _deg) {
		return _deg / (180.0f / (float)M_PI);
	}


	static float Mag(sf::Vector2f _a) {
		return abs(sqrt(_a.x * _a.x + _a.y * _a.y));
	}

	static sf::Vector2f Normalize(sf::Vector2f _a) {
		return (_a / Mag(_a));
	}

	static float Mag(b2Vec2 _a) {
		return abs(sqrt(_a.x * _a.x + _a.y * _a.y));
	}

	static b2Vec2 Normalize(b2Vec2 _a) {
		return ((1.0f / Mag(_a)) * _a);
	}

	static double GetSecondsPast() {
		double test = (double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		return  test / 1000.0;
	}
}
#endif