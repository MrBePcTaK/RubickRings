#ifndef GAMEGRAPHICSVIEW_H
#define GAMEGRAPHICSVIEW_H

#include <QGraphicsView>

class GameGraphicsView : public QGraphicsView
{
public:
    GameGraphicsView();
    void resizeEvent(QResizeEvent *event);
};

#endif // GAMEGRAPHICSVIEW_H
