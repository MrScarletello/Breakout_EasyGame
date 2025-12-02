#include "game.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"
#include <QTimer> // Таймер для відліку
#include <QFont>  // Шрифти для написів "Game Over" тощо

Game::Game(QWidget *parent)
{
    // === Налаштування Вікна ===
    // 1. Створюємо сцену (ігровий світ)
    scene = new QGraphicsScene();
    // Задаємо розмір сцени 800x600 пікселів
    scene->setSceneRect(0, 0, 800, 600);
    // Підключаємо сцену до вікна (QGraphicsView)
    setScene(scene);

    // 2. Вимикаємо смуги прокрутки (щоб вони не з'являлися випадково)
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 3. Фіксуємо розмір вікна, щоб його не можна було розтягувати
    setFixedSize(800, 600);

    // Запускаємо підготовку до гри
    start();
}

void Game::start()
{
    // 1. Очищення сцени.
    // Це критично важливо для перезапуску: видаляє всі старі цеглини, м'ячі та написи.
    scene->clear();

    // 2. Створення Ракетки
    paddle = new Paddle();
    paddle->setPos(350, 550); // Ставимо внизу по центру
    scene->addItem(paddle);

    // Дуже важливо: даємо ракетці "фокус", щоб вона ловила натискання клавіш
    paddle->setFlag(QGraphicsItem::ItemIsFocusable);
    paddle->setFocus();

    // 3. Створення М'яча
    ball = new Ball();
    ball->setPos(400, 500); // Ставимо над ракеткою
    scene->addItem(ball);
    // Ми НЕ запускаємо startMoving() тут. М'яч чекає таймера.

    // 4. Побудова стіни з цеглин
    for (int i = 0; i < 5; ++i) {      // 5 рядків
        for (int j = 0; j < 8; ++j) {  // 8 стовпців
            Brick *brick = new Brick();
            // Математика: зсув 30 пікселів зліва + ширина цеглини * номер стовпця
            brick->setPos(30 + j * 90, 50 + i * 30);
            scene->addItem(brick);
        }
    }

    // === 5. Логіка Зворотного Відліку (3 секунди) ===
    countdownValue = 3; // Починаємо з 3
    countdownText = new QGraphicsTextItem(QString::number(countdownValue));

    // Налаштування шрифту (великий синій текст)
    QFont font("times", 50);
    countdownText->setFont(font);
    countdownText->setDefaultTextColor(Qt::blue);
    countdownText->setPos(380, 300); // Центр екрана
    scene->addItem(countdownText);

    // Створюємо таймер саме для відліку
    countdownTimer = new QTimer(this);
    // Підключаємо його до методу updateCountdown()
    connect(countdownTimer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    // Запускаємо: тікає раз на 1000 мс (1 секунда)
    countdownTimer->start(1000);
}

void Game::updateCountdown()
{
    countdownValue--; // Зменшуємо лічильник (3 -> 2 -> 1 -> 0)

    if (countdownValue > 0) {
        // Якщо ще не 0, просто оновлюємо цифру на екрані
        countdownText->setPlainText(QString::number(countdownValue));
    }
    else if (countdownValue == 0) {
        // Якщо 0, пишемо "GO!"
        countdownText->setPlainText("GO!");
    }
    else {
        // Якщо час вийшов (-1):
        countdownTimer->stop();         // Вимикаємо таймер відліку
        scene->removeItem(countdownText); // Прибираємо напис з екрана
        delete countdownText;           // Звільняємо пам'ять

        ball->startMoving(); // <--- ГОЛОВНИЙ МОМЕНТ: Запускаємо фізику м'яча
    }
}

void Game::restartGame()
{
    // Цей слот викликається кнопкою "Play Again".
    // Ми просто викликаємо start(), який очистить все і почне заново.
    start();
}

void Game::displayGameOver() {
    // 1. Малюємо напис "Game Over"
    QGraphicsTextItem *text = new QGraphicsTextItem("Game Over!");
    QFont font("times", 50);
    text->setFont(font);
    text->setDefaultTextColor(Qt::red);
    text->setPos(200, 200);
    scene->addItem(text);

    // 2. Створюємо кнопку "Play Again"
    Button *playBtn = new Button("Play Again");
    playBtn->setPos(300, 350);
    scene->addItem(playBtn);
    // З'єднуємо клік по кнопці з функцією restartGame()
    connect(playBtn, SIGNAL(clicked()), this, SLOT(restartGame()));

    // 3. Створюємо кнопку "Quit"
    Button *quitBtn = new Button("Quit");
    quitBtn->setPos(300, 425);
    scene->addItem(quitBtn);
    // З'єднуємо клік із закриттям вікна (close)
    connect(quitBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void Game::displayVictory() {
    // Те саме, що й GameOver, тільки текст зелений і пише "You Win!"
    QGraphicsTextItem *text = new QGraphicsTextItem("You Win!");
    QFont font("times", 50);
    text->setFont(font);
    text->setDefaultTextColor(Qt::green);
    text->setPos(250, 200);
    scene->addItem(text);

    // Кнопки ті самі
    Button *playBtn = new Button("Play Again");
    playBtn->setPos(300, 350);
    scene->addItem(playBtn);
    connect(playBtn, SIGNAL(clicked()), this, SLOT(restartGame()));

    Button *quitBtn = new Button("Quit");
    quitBtn->setPos(300, 425);
    scene->addItem(quitBtn);
    connect(quitBtn, SIGNAL(clicked()), this, SLOT(close()));
}
