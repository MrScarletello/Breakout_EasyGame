#ifndef BALL_H
#define BALL_H // Захист від повторного підключення цього файлу (Include Guard)

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer> // Підключаємо бібліотеку для роботи з таймером

// Клас Ball успадковує два класи:
// 1. QObject -> щоб працювали сигнали/слоти (механізм Qt для подій)
// 2. QGraphicsRectItem -> щоб м'яч був видимим графічним об'єктом (квадратом)
class Ball : public QObject, public QGraphicsRectItem
{
    Q_OBJECT // Макрос, обов'язковий для будь-якого класу, що використовує слоти/сигнали
public:
    Ball(QGraphicsItem *parent = nullptr); // Конструктор класу

    double dx; // Змінна для швидкості руху по горизонталі (вісь X)
    double dy; // Змінна для швидкості руху по вертикалі (вісь Y)
    QTimer *timer; // Таймер, який буде "рухати" м'яч через певні проміжки часу

    void startMoving(); // Метод, який ініціалізує та запускає таймер

public slots:
    // Слот — це функція, яка викликається автоматично по сигналу таймера.
    // Тут прописана логіка зміни координат і перевірки зіткнень.
    void move();
};

#endif // BALL_H
