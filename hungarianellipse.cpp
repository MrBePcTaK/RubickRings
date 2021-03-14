#include "hungarianellipse.h"

#include <QDebug>

HungarianEllipse::HungarianEllipse(qreal x, qreal y, int height, int width)
{
    this->setRect(0, 0, height, width);
    setPos(x, y);
}

QPointF HungarianEllipse::getCentrePos() const
{
    auto height = rect().height();
    auto width  = rect().width();
    auto curPos = scenePos();

    return {curPos.x() + (width / 2), curPos.y() + (height / 2)};
}
