#include "ball.h"
#include <QTimer>
#include <QGraphicsScene>
#include "game.h"
#include "paddle.h"
#include "brick.h"

// extern означає, що змінна game оголошена десь в іншому файлі (в main.cpp),
// але ми хочемо мати до неї доступ тут, щоб викликати методи GameOver/Victory.
extern Game *game;

Ball::Ball(QGraphicsItem *parent) : QObject(), QGraphicsRectItem(parent)
{
    // 1. Малюємо м'яч (квадрат 15x15 пікселів)
    setRect(0, 0, 15, 15);

    // 2. Задаємо колір (жовтий)
    setBrush(QBrush(Qt::yellow));

    // 3. Початкова швидкість
    dx = 5;  // Швидкість по горизонталі (+ вправо, - вліво)
    dy = -5; // Швидкість по вертикалі (- вгору, + вниз). Починаємо рух вгору.
}

void Ball::startMoving()
{
    // Створюємо таймер. "this" означає, що таймер належить цьому м'ячу.
    timer = new QTimer(this);

    // З'єднуємо сигнал таймера (timeout) зі слотом руху (move).
    // Кожного разу, коли таймер цокає, викликається функція move().
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // Запускаємо таймер з інтервалом 20 мс (це приблизно 50 кадрів на секунду).
    timer->start(20);
}

void Ball::move()
{
    // === 1. Фізичне переміщення ===
    // Змінюємо координати об'єкта на поточну швидкість
    moveBy(dx, dy);

    // === 2. Відбивання від стін ===
    // Якщо вперлися в ліву (<=0) або праву (>=800) стіну — інвертуємо dx
    if (pos().x() <= 0 || pos().x() + rect().width() >= 800) {
        dx = -1 * dx;
    }

    // === 3. Відбивання від стелі ===
    // Якщо вперлися в верх (<=0) — інвертуємо dy
    if (pos().y() <= 0) {
        dy = -1 * dy;
    }

    // === 4. Перевірка програшу ===
    // Якщо м'яч впав нижче 600 пікселів (дно екрана)
    if (pos().y() > 600) {
        timer->stop();           // Зупиняємо м'яч
        game->displayGameOver(); // Викликаємо екран поразки через глобальний об'єкт гри
        return;                  // Припиняємо виконання функції
    }

    // === 5. Обробка зіткнень з об'єктами ===
    // collidingItems() повертає список усіх об'єктів, яких торкається м'яч
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i) {

        // dynamic_cast перевіряє: "Чи є цей об'єкт Ракеткою?"
        Paddle *paddle = dynamic_cast<Paddle *>(colliding_items[i]);
        if (paddle) {
            dy = -1 * dy; // Відбиваємося
            return;       // Виходимо, щоб не обробляти інші зіткнення в цьому кадрі
        }

        // Перевіряє: "Чи є цей об'єкт Цеглиною?"
        Brick *brick = dynamic_cast<Brick *>(colliding_items[i]);
        if (brick) {
            dy = -1 * dy;               // Відбиваємося
            scene()->removeItem(brick); // Прибираємо цеглину з екрана
            delete brick;               // Звільняємо пам'ять

            // === Перевірка перемоги ===
            // Якщо на сцені лишилося тільки 2 предмети (М'яч і Ракетка), значить цеглин немає
            if (game->scene->items().size() == 2) {
                timer->stop();          // Зупиняємо гру
                game->displayVictory(); // Показуємо перемогу
            }
            return;
        }
    }
}
