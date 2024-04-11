#ifndef MODEL_H
#define MODEL_H

#include "plant.h"
#include "qobject.h"
#include <vector>
#include <QString>
#include <QObject>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    std::vector<Plant*> plants;


public slots:
    void getPlantText();

signals:
    void sendPlantText(QString text);
};

#endif // MODEL_H
