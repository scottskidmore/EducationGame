
#include "scrollarea.h"

ScrollArea::ScrollArea(QWidget *parent)
    : QScrollArea{parent}
{
}

void ScrollArea::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}
