#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QColor>
#include <QPainter>
class Player : public QGraphicsRectItem {
public:
    Player(int screen_w, int screen_h, int w, int h, QColor clr);
    void keyPressEvent(QKeyEvent* event) override;

private:
    int screenWidth;
    int screenHeight;
};

#endif // PLAYER_H
