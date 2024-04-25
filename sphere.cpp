#include "Sphere.h"

Sphere::Sphere(int radius, QColor clr, int screen_w, int screen_h)
    : QGraphicsEllipseItem(-radius, -radius, 2 * radius, 2 * radius) {
    setPos(screen_w / 2, screen_h / 2);
    setBrush(QBrush(clr));
    screenWidth = screen_w;
    screenHeight = screen_h;
}

