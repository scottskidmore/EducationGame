#include "physicsplant.h"

PhysicsPlant::PhysicsPlant(b2World* world, const QString& imagePath, QPoint pos, QWidget* parent) :
    QWidget(parent), world(world), imagePath(imagePath)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x(), pos.y()); // Initial position
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
    this->setGeometry(pos.x(), pos.y(), 1028, 1028);
    // Timer to update the simulation and the widget
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PhysicsPlant::updateSimulation);
    timer->start(16); // Roughly 60 FPS
}

void PhysicsPlant::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawPixmap(this->pos().x() +190, this->pos().y() + 60, image);
}

void PhysicsPlant::updateSimulation() {
    // Step the physics simulation
    //world->Step(1.0f / 60.0f, 6, 2);

    // Get the Box2D body's position
    b2Vec2 position = body->GetPosition();
    // Convert the Box2D position to pixel coordinates and move the widget

    move(position.x * 100, position.y * 100);

    // Redraw the widget
    update();
}
