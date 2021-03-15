#ifndef HUNGARIANRINGPUZZLE_H
#define HUNGARIANRINGPUZZLE_H

// Qt
#include <QGraphicsRectItem>
#include <QObject>
#include <QtMath>
//#include <QBrush>
//#include <QPointF>
//#include <QDebug>

// STL
#include <memory>
#include <stdexcept>
#include <algorithm>

// .H
#include "hungarianellipse.h"
#include "hungarianring.h"
#include "hungarianball.h"
#include "hungarianballinorderspawner.h"
#include "hungarianballsrandomspawner.h"


class HungarianRingPuzzle : public QGraphicsRectItem
{
public /*members*/:

    //! Параметризированный конструктор
    HungarianRingPuzzle(uint8_t numberOfBalls = 18);
    //! Деструктор
    ~HungarianRingPuzzle();

    enum class Ring {
        None,
        Left,
        Right
    };

public /*operations*/:

    void clearGameStat();

    //! ...
    HungarianRing getRingBySide(Ring);
    //! ...
    void rotate(uint8_t count);
    //! ...
    bool rotateSelectedHungarianRing(bool toRight);

    //! ...
    void setSelectedRing(Ring);

    //! ...
    QVector<HungarianBall*> balls() const;

    const uint32_t &numberOfRotations() const;

    //! ...
    bool isGameOver() const;

private /*operations*/:

    //! Поворот выбранного списка игровых шаров
    bool rotateHungarianRing(QVector<HungarianBall*>& hungarianRing, bool toRight);
    //! Создаются игровые кольца
    void createHungarianRings();
    //! Устанавливаются игровые кольца по указателям
    void setHungarinRings(HungarianEllipse* leftRing, HungarianEllipse* rightRing);

    //! Создаются игровые кольца
    void createHungarianBallsSpawner(uint8_t numberOfBalls);
    //! Устанавливаются игровые кольца по указателям
    void setHungarinBallsSpawner(HungarianBallsSpawner* ballsSpawner);

    //! Спавнит игровые шары вокруг игровых колец
    bool createBallsAroundRings(uint8_t numberOfBalls);

protected /*members*/:

    Ring     m_selectedRing = Ring::None;
    uint32_t m_numberOfRotations;

    //! Умный указатель на левое игровому кольцо
    std::unique_ptr<HungarianEllipse> m_leftRing;
    //! Умный указатель на правое игровому кольцо
    std::unique_ptr<HungarianEllipse> m_rightRing;

    //! Умный спавнер игровых шаров
    std::unique_ptr<HungarianBallsSpawner> m_ballSpawner;

    //! Список колец, принадлежащих левому игровому кольцу
    QVector<HungarianBall*>  m_leftBallList;
    //! Список колец, принадлежащих правому игровому кольцу
    QVector<HungarianBall*>  m_rightBallList;
};

#endif // HUNGARIANRINGPUZZLE_H
