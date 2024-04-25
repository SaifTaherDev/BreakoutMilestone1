#ifndef BRICKS_H
#define BRICKS_H

#include <QGraphicsRectItem>
#include <QColor>
#include <QPainter>
class Bricks : public QGraphicsRectItem {
public:
    Bricks(int x, int y, int w, int h, QColor clr);
};

#endif // BRICKS_H
