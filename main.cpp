#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsView>

void init_view(QGraphicsView &view, QGraphicsScene &scene, int w, int h, QColor background)
{
    view.setFixedSize(w, h);
    scene.setSceneRect(0, 0, w, h);

    view.setScene(&scene);
    view.show();

    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setBackgroundBrush(background);
}

void init_player(QGraphicsRectItem* player, int screen_w, int screen_h, int w, int h, QColor clr)
{
    QPen pen(clr);
    player->setBrush(clr);
    player->setPen(pen);
    player -> setRect(screen_w / 2 - w / 2, screen_h * 0.8, w, h);
}

void init_sphere(QGraphicsEllipseItem* sphere, int radius, QColor clr, int screen_w, int screen_h)
{
    QPen pen(clr);
    sphere->setBrush(clr);
    sphere->setPen(pen);
    sphere->setRect(screen_w / 3 - radius, screen_h * 0.6, 2 * radius, 2 * radius);
}

void init_bricks(QGraphicsRectItem* arr, int n_bricks, int n_rows, int screen_w, int screen_h, QColor clr, int margin)
{
    int cursor_x(0), cursor_y(0);
    int bricks_per_row = n_bricks / n_rows;
    int brick_w = (screen_w - (2 + bricks_per_row - 1) * margin) / bricks_per_row;
    int brick_h = (screen_h - (n_rows - 1) * margin) / 2 / n_rows;

    QPen pen(clr);

    for (int i = 0; i < n_rows; i++)
    {
        cursor_x = 0;
        cursor_y += margin;
        for (int j = 0; j < bricks_per_row; j++)
        {
            cursor_x += margin;
            arr[i * bricks_per_row + j].setRect(cursor_x, cursor_y, brick_w, brick_h);
            arr[i * bricks_per_row + j].setBrush(clr);
            arr[i * bricks_per_row + j].setPen(pen);
            cursor_x += brick_w;
        }
        cursor_y += brick_h;
    }

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int screen_w = 1000, screen_h = 800;
    QColor background = QColor(100, 50, 200);

    QGraphicsView view;
    QGraphicsScene scene;
    init_view(view, scene, screen_w, screen_h, background);

    int player_w = 120, player_h = 30;
    QColor player_clr = QColor(255, 255, 255);
    QGraphicsRectItem * player = new QGraphicsRectItem;
    init_player(player, screen_w, screen_h, player_w, player_h, player_clr);
    scene.addItem(player);

    int radius(20), vx(50), vy(50);
    QColor sphere_clr = QColor(255, 215, 0);
    QGraphicsEllipseItem * sphere = new QGraphicsEllipseItem;
    init_sphere(sphere, radius, sphere_clr, screen_w, screen_h);
    scene.addItem(sphere);

    int n_bricks = 30, n_rows = 6, margin = 20;
    QGraphicsRectItem* bricks_arr = new QGraphicsRectItem[n_bricks];
    QColor brick_clr = QColor(255, 20, 0);
    init_bricks(bricks_arr, n_bricks, n_rows, screen_w, screen_h, brick_clr, margin);
    for (int i = 0; i < n_bricks; i++) scene.addItem(&bricks_arr[i]);

    return a.exec();
}
