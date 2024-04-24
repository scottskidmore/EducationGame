#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QScrollArea>

/// \brief ScrollArea - custom QScrollArea to handle mouse press events
class ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    /// \brief Constructor for ScrollArea
    ScrollArea(QWidget *parent = nullptr);

    /// \brief Handles mouse press events within the scroll area
    /// \param QMouseEvent* event - The mouse event that triggered this handler
    void mousePressEvent(QMouseEvent *event) override;
signals:
    /// \brief Signal emitted wen the scroll area is clicked
    void clicked();
};

#endif // SCROLLAREA_H
