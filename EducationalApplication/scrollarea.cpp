#include "scrollarea.h"

/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Implementation file for the Scrollarea class. This class manages events within scroll area objects.
*/
ScrollArea::ScrollArea(QWidget *parent)
    : QScrollArea{parent}
{
}

void ScrollArea::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}
