#ifndef PADDLE_H
#define PADDLE_H // Стандартний захист заголовного файлу

#include <QGraphicsRectItem> // Базовий клас для малювання прямокутника
#include <QKeyEvent>         // Ця бібліотека потрібна, щоб розуміти натискання клавіш

// Клас Paddle успадковує QGraphicsRectItem, бо він виглядає як прямокутник.
// Йому не обов'язково мати Q_OBJECT, якщо ми не використовуємо власні слоти/сигнали,
// а просто перевизначаємо стандартні події (як keyPressEvent).
class Paddle : public QGraphicsRectItem
{
public:
    Paddle(QGraphicsItem *parent = nullptr); // Конструктор

    // Це найважливіший метод для гравця.
    // Ми "перехоплюємо" стандартну подію натискання клавіші.
    // Коли будь-яка кнопка натискається, Qt викликає цю функцію, і ми перевіряємо, чи це стрілочки.
    void keyPressEvent(QKeyEvent *event);
};

#endif // PADDLE_H
