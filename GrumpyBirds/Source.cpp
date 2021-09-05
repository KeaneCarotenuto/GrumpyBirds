#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "box2d/box2d.h"
#include <iostream>

#include "CResourceManager.h"
#include "CBody.h"
#include "CBird.h"
#include "CGame.h"
#include "utility.h"



int FixedUpdate();
void Draw();

//FixedUpdate() call rate
double timeStep = (1.0f / 60.0f);
int32 velocityIterations = 6;
int32 positionIterations = 2;

sf::RenderWindow* window;

CGame* game = CGame::GetInstance();

sf::RenderWindow* util::window = nullptr;

int main()
{
	//window setup
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window =  new sf::RenderWindow(sf::VideoMode(1600, 800), "SFML and box2D works!", sf::Style::Default, settings);
    window->setFramerateLimit(60);
    CBody::SetWindow(window);
	game->SetWindow(window);
	util::window = window;

	CResourceManager::LoadImage("Rect.png");
	CResourceManager::LoadImage("Circle.png");
	CResourceManager::LoadImage("Bird_Regular_1.png");
	CResourceManager::LoadImage("Pig_Regular_1.png");
	CResourceManager::LoadImage("Block_Wood_Regular_1.png");
	CResourceManager::LoadImage("Block_Wood_Circle_1.png");

	//Start Game Scene up
	//InitGameScene();

	//Manages the FixedUpdate() timing
	double stepTime = 0;
	bool drawn = false;

	sf::Clock clock;

	CBird* myBird = nullptr;

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

		if (!CBody::GetToDelete().empty()) CGame::GetInstance()->ClearDeleted();
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
				if (newEvent.key.code == sf::Keyboard::Num3) {
					if (game->GetWorld()) myBird = new CBird(game->GetWorld(), { 226,800 }, 25, b2_dynamicBody, "Circle.png");
				}
				if (newEvent.key.code == sf::Keyboard::Num4) {
					if (myBird) myBird->Destroy();
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