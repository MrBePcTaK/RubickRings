#ifndef HUNGARIANBALLINORDERSPAWNER_H
#define HUNGARIANBALLINORDERSPAWNER_H

#include "hungarianballsspawner.h"

class HungarianBallsInOrderSpawner : public HungarianBallsSpawner
{
    using BallCollection = QVector<HungarianBall*>;
public:
    HungarianBallsInOrderSpawner(uint8_t numberOfBalls);
    QPair<BallCollection, BallCollection> spawn() override;
};

#endif // HUNGARIANBALLINORDERSPAWNER_H
