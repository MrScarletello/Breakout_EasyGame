#ifndef BRICK_H
#define BRICK_H // Стандартний захист заголовного файлу

#include <QGraphicsRectItem> // Підключаємо клас для малювання прямокутників

// Клас Brick успадковує лише QGraphicsRectItem.
// Йому не потрібен QObject, бо цеглина не використовує сигнали/слоти (вона не рухається сама).
class Brick : public QGraphicsRectItem
{
public:
    // Конструктор.
    // parent = nullptr означає, що об'єкт не має "батька" при створенні (він додається на сцену пізніше).
    Brick(QGraphicsItem *parent = nullptr);
};

#endif // BRICK_H
