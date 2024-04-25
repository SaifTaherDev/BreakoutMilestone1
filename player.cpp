#include "Player.h"
#include <QKeyEvent>

Player::Player(int screen_w, int screen_h, int w, int h, QColor clr)
    : QGraphicsRectItem(0, 0, w, h) {
    setRect(0, 0, w, h);
    setBrush(QBrush(clr));
    screenWidth = screen_w;
    screenHeight = screen_h;
}

void Player::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Left) {
        if(x() > 0) // to prevent the player from getting out of the screen
            setPos(x() - 10, y());
    }
    else if(event->key() == Qt::Key_Right) {
        if(x() + 120 < 800) // to prevent the player from getting out of the screen
            setPos(x() + 10, y());
}
}
