#ifndef SPHERE_H
#define SPHERE_H

#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QColor>

class Sphere : public QGraphicsEllipseItem
{
public:
    Sphere(int radius, QColor clr, int screen_w, int screen_h);

    void moveDown();  // Move sphere downward
    void moveUp();    // Move sphere upward

private:
    int screenWidth;
    int screenHeight;
};

#endif // SPHERE_H
