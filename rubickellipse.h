#ifndef RUBICKELLIPSE_H
#define RUBICKELLIPSE_H

#include <QGraphicsEllipseItem>
#include <QObject>

class RubickEllipse : public QGraphicsEllipseItem
{
public:
    RubickEllipse(qreal x, qreal y, int height, int width);
};

#endif // RUBICKELLIPSE_H
