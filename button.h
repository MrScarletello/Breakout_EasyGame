#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject> // Потрібен для роботи сигналів

// Клас Button теж використовує множинне успадкування:
// 1. QObject -> щоб ми могли створити сигнал clicked()
// 2. QGraphicsRectItem -> щоб кнопка виглядала як прямокутник
class Button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT // Обов'язковий макрос для сигналів
public:
    // Конструктор приймає текст (назву кнопки), наприклад "Play"
    Button(QString name, QGraphicsItem *parent = nullptr);

    // Перевизначаємо метод обробки подій миші.
    // Коли хтось клікає по цьому прямокутнику, спрацює ця функція.
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    // Це наш власний сигнал.
    // Ми будемо "випускати" (emit) його, коли відбудеться клік,
    // щоб клас Game знав, що кнопку натиснули.
    void clicked();

private:
    QGraphicsTextItem *text; // Вказівник на текст, що відображається всередині кнопки
};

#endif // BUTTON_H
