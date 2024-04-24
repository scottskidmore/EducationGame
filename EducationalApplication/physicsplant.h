#ifndef PHYSICSPLANT_H
#define PHYSICSPLANT_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include "Box2D/box2d.h"

/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Header file for the PhysicsPlant class. The PhysicsPlant class handles the box2d animations
            for the plants being removed from the stack.
*/
class PhysicsPlant : public QWidget
{
    Q_OBJECT
public:
    ///
    /// \brief PhysicsPlant - constructor
    /// \param world
    /// \param imagePath
    /// \param pos
    /// \param parent
    ///
    explicit PhysicsPlant(b2World* world, const QString& imagePath, QPoint pos, QWidget* parent = nullptr);

private:
    ///
    /// \brief world - represents the Box2D world for the physics of each plant, this is shared between all Physics Plants for the round
    ///
    b2World* world;
    ///
    /// \brief body - the physics body of this PhysicsPlant
    ///
    b2Body* body;
    ///
    /// \brief image - pixmap of the image for the plant being displayed
    ///
    QPixmap image;
    ///
    /// \brief imagePath - the path to the image
    ///
    QString imagePath;

protected:
    ///
    /// \brief paintEvent - overriding the paint for this widget, paints the image of the plant
    /// \param event
    ///
    void paintEvent(QPaintEvent* event);

public slots:
    ///
    /// \brief updateSimulation - gets called whenever the world has been changed and this physics plant needs to move
    ///
    void updateSimulation();
};

#endif // PHYSICSPLANT_H
