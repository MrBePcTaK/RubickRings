#ifndef GAMEBOARD_H
#define GAMEBOARD_H

// Qt
#include <QGraphicsScene>
#include <QObject>
#include <QDebug>
#include <QtMath>
#include <QPair>
#include <QLinkedList>
#include <QMessageBox>

// STL
#include <memory>

// .H
#include "hungarianringpuzzle.h"

class GameBoard : public QGraphicsScene
{
    Q_OBJECT

public /*methods*/:

    explicit GameBoard();
    ~GameBoard();

    void mousePressEvent(QGraphicsSceneMouseEvent  *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  *event) override;

    //! Добавляет "Шары Рубика" на игровую сцену
    bool setHungarianRingPuzzleGameOnBoard();
    //! ...
    void changeSelectedHungaringRing();
    //! ...
    bool isPuzzleGamePlaced() const;
    //! ...
    bool isGameOver() const;
    //! ...
    bool isArounHungarianGame() const;
    //! ...
    void rotatePuzzleGame();

    QRectF size() const;

private /*methods*/:

    bool isAround(const HungarianEllipse& item, const QPointF pos) const;
    //! Создает на сцене новый игровой объект "Кольца Рубика"
    void createHungarianRingPuzzle();
    //! Устанавливает на сцену игровой объект "Кольца Рубика"
    void setHungarianRingPuzzle(HungarianRingPuzzle *hungarianRingPuzzle);

private /*members*/:

    std::unique_ptr<HungarianRingPuzzle> m_hrPuzzle;

    // TODO: Сделать поворот кругов не по нажатию мышки, а
    // в "drag-and-drop" стиле.
    QPointF m_mousePressPos;
    QPointF m_mouseReleasePos;
};

#endif // GAMEBOARD_H
