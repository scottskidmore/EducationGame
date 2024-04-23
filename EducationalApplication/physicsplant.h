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
    b2World* world;
    b2Body* body;
    QPixmap image;
    QString imagePath;
    QPoint realPos;

protected:
    void paintEvent(QPaintEvent* event);

public slots:
    void updateSimulation();

signals:
};

#endif // PHYSICSPLANT_H
