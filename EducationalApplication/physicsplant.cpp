#include "physicsplant.h"

/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Implementation file for the PhysicsPlant class. The PhysicsPlant class handles the box2d animations
            for the plants being removed from the stack.
*/
PhysicsPlant::PhysicsPlant(b2World* world, const QString& imagePath, QPoint pos, QWidget* parent) :
    QWidget(parent), world(world), imagePath(imagePath)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x() +190, pos.y() +60); // Initial position inside physics world, needs to be changed because the position is relative to the stack layout location.
    body = world->CreateBody(&bodyDef);

    // Define the shape and fixture
    b2PolygonShape shape;
    shape.SetAsBox(1.0f, 1.0f); // Define the size of the Box2D body

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;
    body->CreateFixture(&fixtureDef);

    // Load the image
    image.load(imagePath);
    this->setGeometry(pos.x() + 190, pos.y() + 60, 64, 64); // setting up geometry to be 64x64 to match icon size.
}

void PhysicsPlant::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, 64, 64, image);
}

void PhysicsPlant::updateSimulation()
{
    // Get the Box2D body's position
    b2Vec2 position = body->GetPosition();
    // Convert the Box2D position to pixel coordinates and move the widget
    move(position.x, position.y);

    // Redraw the widget
    update();
}
