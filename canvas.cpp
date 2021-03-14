#include "canvas.h"

Canvas::Canvas(int h, int w, QWidget *parent)
    : QGraphicsView(parent),
      m_scene(0, 0, w, h, this),
      m_isKeyPressed(false)
{
    setScene(&m_scene);
    fitInView(m_scene.sceneRect(), Qt::KeepAspectRatio);
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPointF pos = mapToScene(event->pos());
        m_line = new Line(QColor(123, 127, 0), &m_scene);
        m_scene.addItem(m_line);
        m_line->addPoint(pos);
        m_isKeyPressed = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (m_isKeyPressed) {
        QPointF pos = mapToScene(event->pos());
        m_line->addPoint(pos);
    }
}
