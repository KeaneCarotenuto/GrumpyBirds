#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "box2d/box2d.h"
#include "CResourceManager.h"

#include <iostream>

int main()
{
    const double SCALE = 30.0;
    //window
    sf::RenderWindow window(sf::VideoMode(640, 640), "SFML and box2D works!");
    window.setFramerateLimit(60);

    //falling object
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(100, 100));

    //ground
    sf::RectangleShape Gshape;
    Gshape.setSize(sf::Vector2f(800, 100));
    Gshape.setFillColor(sf::Color::Green);

    //create world
    b2Vec2 gravity(0.0, 10.f);
    b2World world(gravity);

    //falling object physics
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(100 / SCALE, 100 / SCALE);
    BodyDef.type = b2_dynamicBody;
    b2Body *boxBody = world.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((100.f / 2) / SCALE, (100.f / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.shape = &Shape;
    boxBody->CreateFixture(&FixtureDef);

    //ground physics
    b2BodyDef gBodyDef;
    gBodyDef.position = b2Vec2(0 / SCALE, 600 / SCALE);
    gBodyDef.type = b2_staticBody;
    b2Body *gBody = world.CreateBody(&gBodyDef);

    b2PolygonShape gShape;
    gShape.SetAsBox((800 / 2) / SCALE, (100 / 2) / SCALE);
    b2FixtureDef gFixtureDef;
    gFixtureDef.density = 0.f;
    gFixtureDef.shape = &gShape;
    gBody->CreateFixture(&gFixtureDef);

    while (window.isOpen())
    {
        world.Step(1 / 60.f, 8, 3);
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (b2Body *BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            if (BodyIterator->GetType() == b2_dynamicBody)
            {
                shape.setOrigin(50, 50);
                shape.setPosition(BodyIterator->GetPosition().x * 30, BodyIterator->GetPosition().y * 30);
                shape.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);

                window.draw(shape);
            }
            else if (BodyIterator->GetType() == b2_staticBody)
            {
                Gshape.setOrigin(400, 50);
                Gshape.setPosition(BodyIterator->GetPosition().x * 30, BodyIterator->GetPosition().y * 30);
                Gshape.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);

                window.draw(Gshape);
            }
        }

        window.display();
    }

    return 0;
}