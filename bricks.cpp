#include "Bricks.h"

Bricks::Bricks(int x, int y, int w, int h, QColor clr)
    : QGraphicsRectItem(x, y, w, h) {
    setRect(x, y, w, h);
    setBrush(QBrush(clr));
}
