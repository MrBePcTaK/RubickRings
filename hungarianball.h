#ifndef HUNGARIANBALL_H
#define HUNGARIANBALL_H

#include "hungarianellipse.h"

class HungarianBall : public HungarianEllipse
{
public:
    HungarianBall(qreal x, qreal y, int height, int width);
    ~HungarianBall() override;
};

inline HungarianBall::~HungarianBall()
{

}

#endif // HUNGARIANBALL_H
