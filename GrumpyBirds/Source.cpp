#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "box2d/box2d.h"
#include <iostream>

#include "CResourceManager.h"
#include "CBody.h"

#define SCALE (double)30.0

int FixedUpdate();
void Draw();

//FixedUpdate() call rate
double timeStep = (1.0f / 60.0f);
int32 velocityIterations = 6;
int32 positionIterations = 2;

b2World* world;
sf::RenderWindow* window;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //window
    window =  new sf::RenderWindow(sf::VideoMode(800, 800), "SFML and box2D works!", sf::Style::Default, settings);
    window->setFramerateLimit(60);
    CBody::SetWindow(window);

    //Manages the FixedUpdate() timing
    double stepTime = 0;
    bool drawn = false;

    sf::Clock clock;

    //create world
    b2Vec2 gravity(0.0, -9.81f);
	world = new b2World(gravity);

    CBody* myBod = new CBody(world, { 200,700 }, { 50,50 }, b2_dynamicBody);
    CBody* myBod2 = new CBody(world, { 226,800 }, { 50,50 }, b2_dynamicBody);
    CBody* myBod3 = new CBody(world, { 226,800 }, 25, b2_dynamicBody);
    CBody* myGround = new CBody(world, { 400,100 }, { 750,100 }, b2_staticBody);

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

			}
		}
	}

	return 0;

    return 0;
}

int FixedUpdate() {
    //step b2D system
    world->Step(timeStep, velocityIterations, positionIterations);

	return 1;
}

void Draw() {
	window->clear();

	for (CBody* _body : CBody::GetAllBodies()) {
		_body->Draw();
	}

	window->display();
}