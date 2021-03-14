#ifndef HUNGARIANELLIPSE_H
#define HUNGARIANELLIPSE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class HungarianEllipse : public QGraphicsEllipseItem
{
public:
    HungarianEllipse(qreal x, qreal y, int height, int width);
    virtual ~HungarianEllipse() = default;
    QPointF getCentrePos() const;

};

#endif // HUNGARIANELLIPSE_H
