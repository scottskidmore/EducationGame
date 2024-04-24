#ifndef PHYSICSPLANT_H
#define PHYSICSPLANT_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include "Box2D/box2d.h"
class PhysicsPlant : public QWidget
{
    Q_OBJECT
public:
    explicit PhysicsPlant(b2World* world, const QString& imagePath, QPoint pos, QWidget* parent = nullptr);

private:
    b2World* world; // Represents the Box2D world for the physics of each plant, this is shared between all Physics Plants for the round.
    b2Body* body; // The physics body of this PhysicsPlant
    QPixmap image; // Pixmap of the image for the plant being displayed
    QString imagePath; // the path to the image

protected:

    /// \brief paintEvent - overriding the paint for this widget, paints the image of the plant
    /// \param event
    void paintEvent(QPaintEvent* event);

public slots:

    /// \brief updateSimulation - gets called whenever the world has been changed and this physics plant needs to move.
    void updateSimulation();

};

#endif // PHYSICSPLANT_H
