#include "button.h"
#include <QBrush> // Клас для "заливки" (кольору фону)
#include <QFont>  // Клас для роботи зі шрифтами

Button::Button(QString name, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    // 1. Малюємо прямокутник кнопки (200x50 пікселів)
    setRect(0, 0, 200, 50);

    // 2. Налаштовуємо "пензлик" (фон кнопки)
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); // Суцільний колір
    brush.setColor(Qt::darkCyan);     // Темно-бірюзовий колір
    setBrush(brush);                  // Застосовуємо заливку

    // 3. Створюємо текст на кнопці (наприклад "Play Again")
    // "this" означає, що текст буде прикріплений до кнопки (якщо рухаємо кнопку, текст їде за нею)
    text = new QGraphicsTextItem(name, this);

    // 4. Математика центрування тексту:
    // (Ширина кнопки / 2) - (Ширина тексту / 2) = координата X для центру
    int xPos = rect().width() / 2 - text->boundingRect().width() / 2;
    int yPos = rect().height() / 2 - text->boundingRect().height() / 2;
    text->setPos(xPos, yPos); // Встановлюємо вирахувану позицію

    // Додаємо можливість реагувати на наведення миші (щоб, наприклад, підсвічувати її)
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Це ключовий момент: коли ми натискаємо мишкою, кнопка "кричить" (emit) сигнал.
    // Цей сигнал почує гра (Game.cpp) і зробить дію (перезапустить гру).
    emit clicked();
}
