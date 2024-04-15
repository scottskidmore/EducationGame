#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QScrollArea>


class ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    ScrollArea(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void clicked();
};

#endif // SCROLLAREA_H
