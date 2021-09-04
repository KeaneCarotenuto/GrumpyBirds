#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "box2d/box2d.h"
#include <iostream>

#include "CResourceManager.h"
#include "CBody.h"
#include "CGame.h"

#define SCALE (double)30.0

int FixedUpdate();
void InitGameScene();
void InitGameScene2();
void Draw();

//FixedUpdate() call rate
double timeStep = (1.0f / 60.0f);
int32 velocityIterations = 6;
int32 positionIterations = 2;

sf::RenderWindow* window;

CGame* game = CGame::GetInstance();

int main()
{
	//window setup
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window =  new sf::RenderWindow(sf::VideoMode(800, 800), "SFML and box2D works!", sf::Style::Default, settings);
    window->setFramerateLimit(60);
    CBody::SetWindow(window);
	game->SetWindow(window);

	CResourceManager::LoadImage("Rect.png");
	CResourceManager::LoadImage("Circle.png");

	//Start Game Scene up
	//InitGameScene();

	//Manages the FixedUpdate() timing
	double stepTime = 0;
	bool drawn = false;

	sf::Clock clock;

	while (window->isOpen() == true)
	{
		stepTime += clock.getElapsedTime().asSeconds();
		clock.restart();

		while (stepTime >= timeStep)
		{
			//Main Loop of Game
			if (FixedUpdate() == 0) return 0;

			stepTime -= timeStep;
			drawn = false;
		}

		CBody::TryDestroys();

		//Draws After Updates
		if (drawn)
		{
			//Not needed, but could help if laggy ?
			//sf::sleep(sf::seconds(0.01f));
		}
		else
		{
			Draw();

			drawn = true;
		}

		sf::Event newEvent;

		//Quit
		while (window->pollEvent(newEvent))
		{
			if (newEvent.type == sf::Event::Closed)
			{
				window->close();
			}

			if (newEvent.type == sf::Event::KeyPressed)
			{
				if (newEvent.key.code == sf::Keyboard::Num1) {
					game->SetLevel(CGame::Level::One);
				}
				if (newEvent.key.code == sf::Keyboard::Num2) {
					game->SetLevel(CGame::Level::Two);
				}
			}
		}
	}

	return 0;

    return 0;
}

int FixedUpdate() {
	game->FixedUpdate();

	return 1;
}

void Draw() {
	window->clear();

	for (CBody* _body : CBody::GetAllBodies()) {
		_body->Draw();
	}

	window->display();
}