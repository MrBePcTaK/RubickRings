#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QObject>

class Line;

class Canvas : public QGraphicsView
{
    Q_OBJECT
public:
       explicit Canvas(int h, int w, QWidget *parent = 0);
public slots:
       void resizeEvent(QResizeEvent *);
protected slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
protected:
    QGraphicsScene m_scene;
    Line *m_line;
    bool m_isKeyPressed;
};

#endif // CANVAS_H
