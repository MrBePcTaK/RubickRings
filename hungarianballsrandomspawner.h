#ifndef HUNGARIANBALLSRANDOMSPAWNER_H
#define HUNGARIANBALLSRANDOMSPAWNER_H

#include "hungarianballsspawner.h"

class HungarianBallsRandomSpawner : public HungarianBallsSpawner
{
    using BallCollection = QVector<HungarianBall*>;
public:
    HungarianBallsRandomSpawner(uint8_t numberOfBalls);
    QPair<BallCollection, BallCollection> spawn() override;
};

#endif // HUNGARIANBALLSRANDOMSPAWNER_H
