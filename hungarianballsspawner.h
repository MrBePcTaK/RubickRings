#ifndef HUNGARIANBALLSSPAWNER_H
#define HUNGARIANBALLSSPAWNER_H

// Qt
#include <QObject>
#include <QVector>
#include <QPair>
#include <QtMath>
#include <QBrush>
#include <QDebug>

// STL
#include <random>

// .H
#include <hungarianball.h>

class HungarianBallsSpawner
{
    using BallCollection = QVector<HungarianBall*>;

public:
    HungarianBallsSpawner(uint8_t numberOfBalls);
    virtual QPair<BallCollection, BallCollection> spawn() = 0;

protected:
    uint8_t m_numberOfBalls;
};

#endif // HUNGARIANBALLSSPAWNER_H
