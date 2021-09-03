#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

#include <iostream>

#include "CBody.h"

#define SCALE (double)30.0

int main()
{
    //window
    sf::RenderWindow* window =  new sf::RenderWindow(sf::VideoMode(800, 800), "SFML and box2D works!");
    window->setFramerateLimit(60);
    CBody::SetWindow(window);

    //create world
    b2Vec2 gravity(0.0, -9.81f);
    b2World world(gravity);

    CBody* myBod = new CBody(&world, { 200,700 }, { 50,50 }, b2_dynamicBody);
    CBody* myBod2 = new CBody(&world, { 226,800 }, { 50,50 }, b2_dynamicBody);
    CBody* myGround = new CBody(&world, { 400,100 }, { 750,100 }, b2_staticBody);


    while (window->isOpen())
    {
        world.Step(1 / 60.f, 8, 3);
        window->clear();

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        for (CBody* _body : CBody::GetAllBodies()) {
            _body->Draw();
        }

        window->display();
    }

    return 0;
}