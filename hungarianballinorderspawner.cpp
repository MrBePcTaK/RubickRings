#include "hungarianballinorderspawner.h"

#include <QtMath>
#include <QBrush>
#include <QDebug>

#include "hungarianring.h"

HungarianBallsInOrderSpawner::HungarianBallsInOrderSpawner(uint8_t numberOfBalls) : HungarianBallsSpawner(numberOfBalls)
{
}

QPair<HungarianBallsInOrderSpawner::BallCollection, HungarianBallsInOrderSpawner::BallCollection> HungarianBallsInOrderSpawner::spawn()
{
    BallCollection leftCollection;
    BallCollection rightCollection;

    HungarianRing m_leftRing(0, 0, 500, 500);
    HungarianRing m_rightRing(250, 0, 500, 500);

    const auto rad         = - M_PI / (m_numberOfBalls / 2); //< 360 / N = 20 градусов
    const auto halfHorRad  = m_leftRing.rect().width() / 2;
    const auto halfVertRad = m_leftRing.rect().height() / 2;
    const auto hrPerimeter = ((4 * (M_PI) * (halfHorRad * halfVertRad) + (halfHorRad - halfVertRad)) /
                             (halfHorRad + halfVertRad));
    const auto ballRad     = hrPerimeter / m_numberOfBalls;

    // Контейнер для хранения указателей на шары
    QVector<HungarianBall*> ballList;

    // Создает шары по внешним сторонам
    auto createBallsAroundHungarianRing = [&](HungarianEllipse* hungarianRing, uint from, uint to, QBrush color)
    {
        auto hrCenterPos = hungarianRing->getCentrePos();

        for (auto radCoeff = from; radCoeff <= to; radCoeff++) {
            auto new_x = hrCenterPos.rx() + halfHorRad * qCos(rad * radCoeff);
            auto new_y = hrCenterPos.ry() + halfVertRad * qSin(rad * radCoeff);

            HungarianBall* newBall = new HungarianBall((new_x - (ballRad /2)),
                                                       (new_y - (ballRad) / 2),
                                                       ballRad, ballRad);
            newBall->setBrush(color);
            ballList.push_back(newBall);
        }
    };

    // Рисуем левый внешний набор шаров
    createBallsAroundHungarianRing(&m_leftRing, 4, 14, QBrush(Qt::GlobalColor::red)); // 4-14
    // Рисуем правый внутренний набор шаров
    createBallsAroundHungarianRing(&m_leftRing, 15, 20, QBrush(Qt::GlobalColor::yellow)); // 15-20
    // Рисуем левый внутренний набор шаров
    createBallsAroundHungarianRing(&m_rightRing, 6, 11, QBrush(Qt::GlobalColor::yellow)); // 6-11
    // Рисуем правый внешний набор шаров
    createBallsAroundHungarianRing(&m_rightRing, 13, 23, QBrush(Qt::GlobalColor::blue)); // 13-23

    // Заполняем список левых "Шаров Рубика"
    for (int idx = 0; idx < 18; ++idx) {
        leftCollection.push_back(ballList[idx]);
    }

    // Заполняем список правых "Шаров Рубика"
    for (int idx = 0; idx < 17; ++idx) {
        if (idx == 6) {
            rightCollection.push_back(ballList[11]);
        }
        rightCollection.push_back(ballList[idx + 17]);
    }

    return qMakePair(leftCollection, rightCollection);
}
