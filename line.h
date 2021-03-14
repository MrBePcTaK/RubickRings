#ifndef LINE_H
#define LINE_H

#include <QGraphicsItemGroup>
#include <QObject>
#include <QPen>
#include <QBrush>

class Line : public QGraphicsItemGroup, public QObject
{
    const int EllipseRadius = 3;
    const int LineWidth = 1;

public:
    Line(const QColor &color, QObject *parent = 0);
    void removePoint();
public slots:
    void addPoint(QPointF point);
protected:
    QGraphicsEllipseItem *m_lastPoint;
};

#endif // LINE_H
