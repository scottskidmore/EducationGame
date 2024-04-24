/*
Authors:    Scott Skidmore, Patrick Schlegel, Tanner Rowlett, Paolo Diotaiuti, Drew Humphrey, Adam Bentley.
Course:     CS 3505, University of Utah, School of Computing
Date:       23 April 2024
Assignment: Educational App
            Header file for the Scrollarea class. This class manages events within scroll area objects.
*/
#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QScrollArea>
///
/// \brief ScrollArea - custom QScrollArea to handle mouse press events
///
class ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    ///
    /// \brief Constructor for ScrollArea
    ///
    ScrollArea(QWidget *parent = nullptr);
    ///
    /// \brief Handles mouse press events within the scroll area
    /// \param QMouseEvent* event - The mouse event that triggered this handler
    ///
    void mousePressEvent(QMouseEvent *event) override;
signals:
    ///
    /// \brief Signal emitted when the scroll area is clicked
    ///
    void clicked();
};

#endif // SCROLLAREA_H
