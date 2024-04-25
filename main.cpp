#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <cmath>
#include <QDebug>
#include <QGraphicsTextItem> // Include for text item
#include <QTime> // Include for delay
#include "Player.h"
#include "Sphere.h"
#include "Bricks.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QGraphicsView view;
    view.setFixedSize(800, 600);
    QColor background = QColor(255, 255, 255);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setBackgroundBrush(background);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 600);

    int score = 0; // Score variable
    int health = 3; // Health variable
    QList<Bricks*> destroyedBricks; // List to store destroyed bricks

    Player* player = new Player(view.width(), view.height(), 120, 30, QColor(215, 214, 213));
    player->setPos(view.width() / 2 - 120 / 2, view.height() - 60);
    scene.addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    Sphere* sphere = new Sphere(20, QColor(53, 50, 47), view.width(), view.height());
    sphere->setPos(view.width() / 2, view.height() / 2);  // Set the initial position at the center of the scene
    double angle = -M_PI_4;  // Initial angle in radians (-45 degrees)
    double speed = 5.0;  // Speed of the sphere
    scene.addItem(sphere);

    // Create Bricks
    int n_bricks = 30, n_rows = 6, margin = 20;
    int bricks_per_row = n_bricks / n_rows;
    int brick_w = (view.width() - (2 + bricks_per_row - 1) * margin) / bricks_per_row;
    int brick_h = (view.height() - (n_rows - 1) * margin) / 2 / n_rows;
    QColor brick_clr = QColor(20, 20, 140);
    int cursor_y = margin;

    for (int i = 0; i < n_rows - 2; i++) {
        int cursor_x = margin;
        for (int j = 0; j < bricks_per_row; j++) {
            Bricks* brick = new Bricks(cursor_x, cursor_y, brick_w, brick_h, brick_clr);
            scene.addItem(brick);
            cursor_x += margin + brick_w;
        }
        cursor_y += margin + brick_h;
    }

    view.setScene(&scene);
    view.show();

    // Score text item
    QGraphicsTextItem scoreText;
    scoreText.setPlainText("Score: 0");
    QFont font;
    font.setPixelSize(20);
    scoreText.setFont(font);
    scoreText.setDefaultTextColor(Qt::black);
    scoreText.setPos(view.width() - 300, view.height() - 50); // Position at bottom right
    scene.addItem(&scoreText);

    // Health text item
    QGraphicsTextItem healthText;
    healthText.setPlainText("Health: " + QString::number(health));
    healthText.setFont(font);
    healthText.setDefaultTextColor(Qt::black);
    healthText.setPos(view.width() - 150, view.height() - 50); // Position at bottom right
    scene.addItem(&healthText);

    // Create a timer to update the game state
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        // Move the sphere
        double dx = speed * cos(angle);
        double dy = speed * sin(angle);

        // Handle the special case when the angle is close to 90 degrees
        if (angle > M_PI_2 - 0.1 && angle < M_PI_2 + 0.1) {
            // Move the sphere only vertically
            sphere->setY(sphere->y() + dy);
        } else {
            // Move the sphere both horizontally and vertically
            sphere->setPos(sphere->x() + dx, sphere->y() + dy);
        }

        // Check for collisions with walls
        if (sphere->x() <= 0 || sphere->x() >= view.width() - sphere->boundingRect().width()) {
            angle = M_PI - angle;  // Reflect the angle on collision with side walls
        } else if (sphere->y() <= 0) {
            angle = -angle;  // Reflect the angle on collision with top wall
        } else if (sphere->y() >= view.height()) {
            // Ball falls
            health--; // Decrease health
            healthText.setPlainText("Health: " + QString::number(health));  // Update the health text
            sphere->setPos(view.width() / 2, view.height() / 2); // Reset ball position
            destroyedBricks.clear(); // Clear the list of destroyed bricks
        }

        // Check for collision between the ball and the player
        if (sphere->collidesWithItem(player)) {
            // Ball and player collide
            angle = -angle;  // Reflect the angle
        }

        QList<QGraphicsItem*> collidingItems = sphere->collidingItems();
        for (QGraphicsItem* item : collidingItems) {
            if (dynamic_cast<Bricks*>(item)) {
                // Brick collision
                scene.removeItem(item);  // Remove the collided brick from the scene
                angle = -angle;  // Reflect the angle on collision with a brick
                score++;  // Increment the score
                scoreText.setPlainText("Score: " + QString::number(score));  // Update the score text
                Bricks* brick = dynamic_cast<Bricks*>(item);
                destroyedBricks.append(brick); // Add destroyed brick to the list
                delete item;  // Free the memory allocated for the brick
                if (score == 20) {
                    // Display Congratulations message
                    QGraphicsTextItem* congratsText = new QGraphicsTextItem("Congratulations!");
                    QFont font;
                    font.setPixelSize(40);
                    congratsText->setFont(font);
                    congratsText->setDefaultTextColor(Qt::black);
                    congratsText->setPos((view.width() - congratsText->boundingRect().width()) / 2,
                                         (view.height() - congratsText->boundingRect().height()) / 2);
                    scene.addItem(congratsText);

                    // Timer to close the application after 5 seconds
                    QTimer::singleShot(1000, [&]() {
                        view.close();
                    });
                }
                break;  // Exit the loop after handling the first collision
            }
        }

        if (health == 0) {
            // Game over if health is zero
            timer.stop();
            qDebug() << "Game Over!";
            QGraphicsTextItem* gameOverText = new QGraphicsTextItem("Game Over!");
            QFont font;
            font.setPixelSize(40);
            gameOverText->setFont(font);
            gameOverText->setDefaultTextColor(Qt::black);
            gameOverText->setPos((view.width() - gameOverText->boundingRect().width()) / 2,
                                 (view.height() - gameOverText->boundingRect().height()) / 2);
            scene.addItem(gameOverText);
            // Timer to close the application after 5 seconds
            QTimer::singleShot(1000, [&]() {
                view.close();
            });
            return;
        }
    });

    // Start the game timer
    timer.start(25);  // Update the game state every 16 milliseconds

    return a.exec();
}
