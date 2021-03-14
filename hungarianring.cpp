#include "hungarianring.h"


HungarianRing::HungarianRing(qreal x, qreal y, int height, int width) : HungarianEllipse(x, y, height, width)
{
    this->setFlags({QGraphicsItem::ItemIsFocusable});
}

HungarianRing::~HungarianRing()
{
}
