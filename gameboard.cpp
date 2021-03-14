#include "gameboard.h"

GameBoard::GameBoard()
{
    createHungarianRingPuzzle();
}

GameBoard::~GameBoard()
{
}

void GameBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    // Запоминаем позицию мыши
    m_mousePressPos = event->scenePos();

    // Меняем рабочий элемент сцены.
    changeSelectedHungaringRing();

    bool toRight = (event->button() == Qt::RightButton) ? true : false;

    m_hrPuzzle->rotateSelectedHungarianRing(toRight);

    // Уведомляем модель, что пользователь нажал кнопку мыши.
    QGraphicsScene::mousePressEvent(event);
}

void GameBoard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // Запоминаем позицию мыши
    m_mouseReleasePos = event->scenePos();

    // Уведомляем модель, что пользователь отпустил кнопку мыши.
    QGraphicsScene::mouseReleaseEvent(event);
}

bool GameBoard::isAround(const HungarianEllipse& item, const QPointF pos) const
{
    // источник: https://www.geeksforgeeks.org/check-if-a-point-is-inside-outside-or-on-the-ellipse
    // источник: https://math.stackexchange.com/questions/76457/check-if-a-point-is-within-an-ellipse

    const auto maxDiff = 0.35; // 0.35

    auto itemCenterPos = item.getCentrePos();
    auto itemHeight    = item.rect().height();
    auto itemWidth     = item.rect().width();

    auto coefficient  = qPow((pos.x() - itemCenterPos.x()), 2) / qPow((itemWidth / 2), 2) +
                        qPow((pos.y() - itemCenterPos.y()), 2) / qPow((itemHeight / 2), 2);

    return ((coefficient >= 1 - maxDiff) && (coefficient <= 1 + maxDiff));
}

void GameBoard::createHungarianRingPuzzle()
{
    setHungarianRingPuzzle(new HungarianRingPuzzle);
}

void GameBoard::setHungarianRingPuzzle(HungarianRingPuzzle *hungarianRingPuzzle)
{
    m_hrPuzzle.reset(hungarianRingPuzzle);
    setHungarianRingPuzzleGameOnBoard();
}

bool GameBoard::setHungarianRingPuzzleGameOnBoard()
{
    for (auto& ball : m_hrPuzzle->balls()) {
        addItem(ball);
    }

    return true;
}

void GameBoard::changeSelectedHungaringRing()
{
    HungarianRing leftRing  = m_hrPuzzle->getRingBySide(HungarianRingPuzzle::Ring::Left);
    HungarianRing rightRing = m_hrPuzzle->getRingBySide(HungarianRingPuzzle::Ring::Right);

    bool isAroundLeftHungardianRing  = isAround(leftRing, m_mousePressPos);
    bool isAroundRightHungardianRing = isAround(rightRing, m_mousePressPos);

    // Если положение мыши не лежит в пределах допустимого к границам "Колец Рубика", прерываем
    // выполнение операции.
    if ((isAroundLeftHungardianRing  == false) && (isAroundRightHungardianRing == false)) {
        m_hrPuzzle->setSelectedRing(HungarianRingPuzzle::Ring::None);
        return;
    }

    if ((isAroundLeftHungardianRing) && !(isAroundRightHungardianRing)) {
        // Если мышь находится в пределах левого кольца, но не в пределах
        m_hrPuzzle->setSelectedRing(HungarianRingPuzzle::Ring::Left);
    } else if (!(isAroundLeftHungardianRing) && (isAroundRightHungardianRing)) {
        // Если мышь находится в пределах правого кольца, но не в пределах левого
        m_hrPuzzle->setSelectedRing(HungarianRingPuzzle::Ring::Right);
    } else {
        // Если мышь находится в пределах и левого, и правого кольца
        QLineF lineFromMousePosToLeftRing(m_mousePressPos, leftRing.getCentrePos());
        QLineF lineFromMousePosToRightRing(m_mousePressPos, rightRing.getCentrePos());

        qreal distanceToLeftRing  = lineFromMousePosToLeftRing.length();
        qreal distanceToRightRing = lineFromMousePosToRightRing.length();

        if (distanceToLeftRing > distanceToRightRing) {
            m_hrPuzzle->setSelectedRing(HungarianRingPuzzle::Ring::Left);
        } else if (distanceToLeftRing < distanceToRightRing) {
            m_hrPuzzle->setSelectedRing(HungarianRingPuzzle::Ring::Right);
        } else if (distanceToLeftRing == distanceToRightRing) {
            m_hrPuzzle->setSelectedRing(HungarianRingPuzzle::Ring::Right);
        }
    }

}

bool GameBoard::isPuzzleGamePlaced() const
{
    return static_cast<bool>(m_hrPuzzle.get());
}

bool GameBoard::isGameOver() const
{
    return m_hrPuzzle->isGameOver();
}

void GameBoard::rotatePuzzleGame()
{
    m_hrPuzzle->rotate(16);
}

QRectF GameBoard::size() const
{
    return itemsBoundingRect();
}

bool GameBoard::isArounHungarianGame() const
{
    return isAround(m_hrPuzzle->getRingBySide(HungarianRingPuzzle::Ring::Left), m_mousePressPos) ||
           isAround(m_hrPuzzle->getRingBySide(HungarianRingPuzzle::Ring::Right), m_mousePressPos);
}
