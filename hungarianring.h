#ifndef HUNGARIANRING_H
#define HUNGARIANRING_H

#include "hungarianellipse.h"

class HungarianRing : public HungarianEllipse
{
public:
    HungarianRing(qreal x, qreal y, int height, int width);
    ~HungarianRing() override;
};

#endif // HUNGARIANRING_H
