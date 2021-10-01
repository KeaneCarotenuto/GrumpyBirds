// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2021 Media Design School
//
// File Name   : Source.cpp
// Description : Main file for the Angry Birds clone
// Authors     : Keane Carotenuto, Nerys Thamm
// Mail        : KeaneCarotenuto@gmail.com, nerysthamm@gmail.com

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "box2d/box2d.h"

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

sf::RenderWindow *window;

CGame *game = CGame::GetInstance();

sf::RenderWindow *util::window = nullptr;

sf::Text instructions;

/// <summary>
/// Setup and then running of the main loop.
/// <para>Author: Keane</para>
/// </summary>
/// <returns></returns>
int main()
{
	//window setup
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window = new sf::RenderWindow(sf::VideoMode(1600, 800), "SFML and box2D works!", sf::Style::Default, settings);
	window->setFramerateLimit(60);
	CBody::SetWindow(window);
	game->SetWindow(window);
	util::window = window;
	std::vector<sf::Drawable *> toDraw = {};

	CResourceManager::LoadImage("Rect.png");
	CResourceManager::LoadImage("Circle.png");
	CResourceManager::LoadImage("ground.png");
	CResourceManager::LoadImage("grass.png");
	CResourceManager::LoadImage("Bird_Regular_1.png");
	CResourceManager::LoadImage("Bird_Fast_1.png");
	CResourceManager::LoadImage("Pig_Regular_1.png");
	CResourceManager::LoadImage("Block_Wood_Regular_1.png");
	CResourceManager::LoadImage("Block_Wood_Circle_1.png");

	CResourceManager::LoadFont("angrybirds.ttf");

	instructions.setFont(*CResourceManager::GetFont("angrybirds.ttf"));
	instructions.setPosition({20, 20});
	instructions.setCharacterSize(25);
	instructions.setString(
		"Press [1] to start the level.\n"
		"Press [2] to clear the level.\n"
		"Drag and Release the raised bird to shoot.\n"
		"Level will clear after 5 seconds of last bird being shot.");

	//Start Game Scene up
	//InitGameScene();

	//Manages the FixedUpdate() timing
	double stepTime = 0;
	bool drawn = false;

	sf::Clock clock;

	CBird *myBird = nullptr;

	while (window->isOpen() == true)
	{
		stepTime += clock.getElapsedTime().asSeconds();
		clock.restart();

		while (stepTime >= timeStep)
		{
			//Main Loop of Game
			if (FixedUpdate() == 0)
				return 0;

			stepTime -= timeStep;
			drawn = false;
		}

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

		if (!CBody::GetToDelete().empty())
			CGame::GetInstance()->ClearDeleted();
		CBody::TryDestroys();

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
				if (newEvent.key.code == sf::Keyboard::Num1)
				{
					game->SetLevel(CGame::Level::One);
				}
				if (newEvent.key.code == sf::Keyboard::Num2)
				{
					game->Clear();
				}
			}
		}
	}

	return 0;

	return 0;
}

int FixedUpdate()
{
	game->FixedUpdate();

	return 1;
}

void Draw()
{
	window->clear();

	for (CBody *_body : CBody::GetAllBodies())
	{
		_body->Draw();
	}
	game->DrawAllTemps();

	window->draw(instructions);

	window->display();
}