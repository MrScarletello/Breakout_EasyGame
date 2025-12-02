#ifndef GAME_H
#define GAME_H // Стандартний захист від повторного підключення

#include <QGraphicsView> // Клас "Вікно" — це те, що бачить гравець
#include <QGraphicsScene> // Клас "Сцена" — це контейнер, де лежать всі об'єкти
#include <QGraphicsTextItem> // Клас для відображення тексту на екрані
#include <QTimer>            // Таймер для відліку часу

// Підключаємо заголовні файли наших об'єктів, щоб Game знав про їх існування
#include "button.h"
#include "ball.h"
#include "paddle.h"

// Клас Game сам по собі є Вікном (успадковує QGraphicsView)
class Game : public QGraphicsView
{
    Q_OBJECT // Найважливіший макрос Qt. Без нього не працюватимуть Слоти (restartGame тощо)
public:
    Game(QWidget *parent = 0); // Конструктор

    QGraphicsScene *scene; // Вказівник на сцену (наш ігровий світ)
    Ball *ball;            // Зберігаємо доступ до м'яча, щоб запускати/зупиняти його
    Paddle *paddle;        // Зберігаємо доступ до ракетки

    // === Змінні для таймера зворотного відліку (3... 2... 1...) ===
    QTimer *countdownTimer; // Таймер, який тікає раз на секунду
    QGraphicsTextItem *countdownText; // Текстове поле, яке показує цифри "3", "2", "1"
    int countdownValue;     // Просто число (лічильник), яке ми зменшуємо

    // === Функції керування станом гри ===
    void displayMainMenu(); // (Опціонально) Показати головне меню
    void start();           // Головна функція: очищає гру і створює нові об'єкти
    void displayGameOver(); // Малює екран поразки + кнопки
    void displayVictory();  // Малює екран перемоги + кнопки

public slots:
    // СЛОТИ — це функції, які реагують на події (сигнали)
    void restartGame();     // Цей слот спрацює, коли натиснуть кнопку "Play Again"
    void updateCountdown(); // Цей слот викликається таймером щосекунди, щоб змінити цифру
};

#endif // GAME_H // Кінець файлу
