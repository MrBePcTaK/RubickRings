#include "rubickellipse.h"

RubickEllipse::RubickEllipse(qreal x, qreal y, int height, int width)
{
    this->setRect(x, y, height, width);

    // Сообщаем о том, что объект может быть задействован в сцене.
    this->setFlag(QGraphicsItem::ItemIsFocusable);
}
