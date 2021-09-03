#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "box2d/box2d.h"
#include <iostream>

#include "CResourceManager.h"
#include "CBody.h"

#define SCALE (double)30.0

int FixedUpdate();
void InitGameScene();
void InitGameScene2();
void Draw();

//FixedUpdate() call rate
double timeStep = (1.0f / 60.0f);
int32 velocityIterations = 6;
int32 positionIterations = 2;

b2World* world;
sf::RenderWindow* window;

int main()
{
	//window setup
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window =  new sf::RenderWindow(sf::VideoMode(800, 800), "SFML and box2D works!", sf::Style::Default, settings);
    window->setFramerateLimit(60);
    CBody::SetWindow(window);

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
					InitGameScene();
				}
				if (newEvent.key.code == sf::Keyboard::Num2) {
					InitGameScene2();
				}
			}
		}
	}

	return 0;

    return 0;
}

void InitGameScene()
{
	for (CBody* _body : CBody::GetAllBodies()) {
		_body->Destroy();
	}

	//create world
	b2Vec2 gravity(0.0, -9.81f);
	world = new b2World(gravity);

	CBody* circleBody = new CBody(world, { 226,800 }, 25, b2_dynamicBody, "Circle.png");
	CBody* squareBody = new CBody(world, { 200,700 }, { 50,50 }, b2_dynamicBody, "Rect.png");
	CBody* rectBody = new CBody(world, { 226,800 }, { 100,50 }, b2_dynamicBody, "Rect.png");
	
	CBody* myGround = new CBody(world, { 400,100 }, { 750,100 }, b2_staticBody, "Rect.png");
}

void InitGameScene2()
{
	for (CBody* _body : CBody::GetAllBodies()) {
		_body->Destroy();
	}

	//create world
	b2Vec2 gravity(0.0, -9.81f);
	world = new b2World(gravity);

	CBody* circleBody = new CBody(world, { 426,800 }, 25, b2_dynamicBody, "Circle.png");
	CBody* squareBody = new CBody(world, { 200,300 }, { 50,50 }, b2_dynamicBody, "Rect.png");

	CBody* myGround = new CBody(world, { 400,100 }, { 750,100 }, b2_staticBody, "Rect.png");
	myGround->GETBODY_TODELETE()->SetTransform(myGround->GETBODY_TODELETE()->GetPosition(), 10 * (M_PI / 180.0));
}

int FixedUpdate() {
    //step b2D system
    if (world) world->Step(timeStep, velocityIterations, positionIterations);

	return 1;
}

void Draw() {
	window->clear();

	for (CBody* _body : CBody::GetAllBodies()) {
		_body->Draw();
	}

	window->display();
}