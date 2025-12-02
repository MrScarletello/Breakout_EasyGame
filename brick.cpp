#include "brick.h"
#include <QBrush> // Підключаємо клас "Пензлик" для зафарбовування фігур

Brick::Brick(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    // 1. Встановлюємо розміри та межі цеглини.
    // x=0, y=0 (локальні координати), ширина=90, висота=30.
    setRect(0, 0, 90, 30);

    // 2. Налаштування кольору
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); // Вказуємо, що заливка має бути суцільною (не в крапочку/смужку)
    brush.setColor(Qt::gray);         // Встановлюємо сірий колір
    setBrush(brush);                  // Застосовуємо цей колір до об'єкта
}
