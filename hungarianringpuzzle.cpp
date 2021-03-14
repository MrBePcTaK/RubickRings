#include "hungarianringpuzzle.h"

HungarianRingPuzzle::HungarianRingPuzzle(uint8_t numberOfBalls)
{
    createHungarianRings();
    createHungarianBallsSpawner(numberOfBalls);
    createBallsAroundRings(numberOfBalls);
}

HungarianRingPuzzle::~HungarianRingPuzzle()
{
}

HungarianRing HungarianRingPuzzle::getRingBySide(HungarianRingPuzzle::Ring ring)
{
    switch (ring) {
    case HungarianRingPuzzle::Ring::None:
        throw std::logic_error("выбран неверный режим");
    case HungarianRingPuzzle::Ring::Left:
        return HungarianRing(0,0, m_leftRing->rect().height(), m_leftRing->rect().width());
    case HungarianRingPuzzle::Ring::Right:
        return HungarianRing(250,0, m_rightRing->rect().height(), m_rightRing->rect().width());
    }
}

void HungarianRingPuzzle::setSelectedRing(HungarianRingPuzzle::Ring selectedRing)
{
    m_selectedRing = selectedRing;
}

bool HungarianRingPuzzle::rotateHungarianRing(QVector<HungarianBall*>& ballList, bool toRight)
{
    if (ballList.size() < 2) {
        return false;
    }

    // TODO: перегрузить оператор присваивания (по цвету)
    // для HungarianBall, чтобы сделать std::swap по списку

    if (toRight) {
        for (int i = 0; i < ballList.size() - 1; i++) {
            auto tmpBrush = ballList[i]->brush();
            ballList[i]->setBrush(ballList[i + 1]->brush());
            ballList[i + 1]->setBrush(tmpBrush);
        }
    } else {
        for (int i = ballList.size() - 1; i > 0; i--) {
            auto tmpBrush = ballList[i]->brush();
            ballList[i]->setBrush(ballList[i - 1]->brush());
            ballList[i - 1]->setBrush(tmpBrush);
        }
    }

    return true;
}

bool HungarianRingPuzzle::rotateSelectedHungarianRing(bool toRight)
{
    switch (m_selectedRing) {
    case Ring::None:
        return false;
    case Ring::Left:
        rotateHungarianRing(m_leftBallList, toRight);
        break;
    case Ring::Right:
        rotateHungarianRing(m_rightBallList, toRight);
        break;
    }

    return true;
}

QVector<HungarianBall *> HungarianRingPuzzle::balls() const
{
    return (m_leftBallList + m_rightBallList);
}

void HungarianRingPuzzle::rotate(uint8_t count)
{
    srand(time(NULL));
    for (uint8_t i = 0; i < count; i++) {
        if (uint8_t randomCoef= rand() % 2 + 1; randomCoef == 1) {
            rotateHungarianRing(m_leftBallList, true);
        } else {
            rotateHungarianRing(m_rightBallList, true);
        }
    }

}

bool HungarianRingPuzzle::isGameOver() const
{
    auto numberOfYellowBalls = [this](auto ballList, auto from, auto to) {
        return std::count_if(ballList.begin() + from, ballList.begin() + to, [&](HungarianBall* hb) {
            return hb->brush().color() == QColor(Qt::yellow);
        });
    };

    auto ballsOnLeft = numberOfYellowBalls(m_leftBallList, 11, m_leftBallList.size());
    auto ballsOnRight = numberOfYellowBalls(m_rightBallList, 0, 7);

//    qDebug() << ballsOnLeft << ballsOnRight;

    return (ballsOnLeft == 7) && (ballsOnRight == 7);
}

void HungarianRingPuzzle::createHungarianRings()
{
    //! HungarianEllipse -> HungarianRing
    setHungarinRings(new HungarianRing(0, 0, 500, 500), new HungarianRing(250, 0, 500, 500));
}

void HungarianRingPuzzle::setHungarinRings(HungarianEllipse *leftRing, HungarianEllipse *rightRing)
{
    m_leftRing.reset(leftRing);
    m_rightRing.reset(rightRing);
}

void HungarianRingPuzzle::createHungarianBallsSpawner(uint8_t numberOfBalls)
{
    setHungarinBallsSpawner(new HungarianBallsInOrderSpawner(numberOfBalls));
}

void HungarianRingPuzzle::setHungarinBallsSpawner(HungarianBallsSpawner *ballsSpawner)
{
    m_ballSpawner.reset(ballsSpawner);
}

bool HungarianRingPuzzle::createBallsAroundRings(uint8_t numberOfBalls)
{
    // Если на доске нет игровых колец, прерываем операцию.
    if (m_leftRing.get() == nullptr || m_rightRing.get() == nullptr) {
        return false;
    }

    auto [left, right] = m_ballSpawner->spawn();
    m_leftBallList = left;
    m_rightBallList = right;

    return true;
}
