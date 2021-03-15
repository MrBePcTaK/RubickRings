#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QString>

#include <QWheelEvent>

GameScreen::GameScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameScreen)
    , m_gameScene(new GameBoard)
{
    ui->setupUi(this);

    // Устанавливаем название окна, в нашем случае это название игры.
    this->setWindowTitle("Игра \"Кольца Кубика\"");

    // ...
    ui->gameStat->setEnabled(false);

    // Устанавливаем новую игровую доску.
    newGameBoard();
    // Начинаем игру.
    startGame();

    // Если игра завершена, отключаем игровое окно и показывает окно "Завершение игры"
    connect(this, &GameScreen::gameOver, [this] { setGameScreenInteractive(false); displayGameOverWindow(); });
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::mousePressEvent(QMouseEvent *event)
{
    if (m_gameScene->isArounHungarianGame()) {
        ui->gameStat->setText(QString::number(m_gameScene->numberOfRotations()));
    }

    if (m_gameScene->isGameOver()) {
        // ...
        emit gameOver();
    }

    QMainWindow::mousePressEvent(event);
}

void GameScreen::newGameBoard()
{
    createGameBoard();
}

void GameScreen::createGameBoard()
{
    setGameBoard(new GameBoard);
}

void GameScreen::setGameBoard(GameBoard* scene)
{
    ui->graphicsView->setScene(scene);
    m_gameScene.reset(scene);
}

bool GameScreen::startGame()
{
    if (m_gameScene->isPuzzleGamePlaced() == false) {
        return false;
    }

    m_gameScene->clearHungarianGameStat();
    ui->gameStat->setText(QString::number(m_gameScene->numberOfRotations()));

    setGameScreenInteractive(true);
    m_gameScene->rotatePuzzleGame();
}

void GameScreen::about()
{
    QMessageBox mb(this);
    mb.setTextFormat(Qt::RichText);
    mb.setWindowTitle("Информация о программе");
    mb.setIcon(QMessageBox::Information);

    // Чтобы перенести текст на новую строчку, необходимо написать в конце
    // строки <br>
    mb.setText("Автор: Борис Плисенко Максимович <br>"
               "Группа: КИ19-08Б <br>"
               "Игра: Кольца Рубика");
    mb.exec();
}

void GameScreen::displayGameOverWindow()
{
    QMessageBox saveQuery(this);
    //
    saveQuery.setIcon(QMessageBox::Question);

    saveQuery.setWindowTitle("Кольца Рубика");
    saveQuery.setText(
                QString("Поздравляем! Вы решили головомку \"Кольца Рубика\". <br>"
                        "Количество ходов: %1. Хотите попробовать ещё раз?").arg(m_gameScene->numberOfRotations()));

    // Добавляем к нашему окну две кнопки: "Принять" и "Отменить"
    saveQuery.setStandardButtons(QMessageBox::Apply | QMessageBox::Discard);

    // Меняем текст кнопок со стандартных на пользовательские
    saveQuery.setButtonText(QMessageBox::Apply, "Да");
    saveQuery.setButtonText(QMessageBox::Discard, "Нет");

    // Кнопка по умолчанию
    saveQuery.setDefaultButton(QMessageBox::Apply);

    switch (saveQuery.exec())
    {
    case QMessageBox::Apply: // Сохранить
        startGame();
        break;
    case QMessageBox::Discard: // Закрыть без сохранения
        break;
    }
}

void GameScreen::setGameScreenInteractive(bool interactiveState)
{
    ui->graphicsView->setInteractive(interactiveState);
}

void GameScreen::wheelEvent(QWheelEvent *event)
{
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    static const double scaleFactor = 1.15;
    static double currentScale = 1.0;
    static const double scaleMin = .1;

    if (event->delta() > 0) {
        ui->graphicsView->scale(scaleFactor, scaleFactor);
        currentScale *= scaleFactor;
    } else if (currentScale > scaleMin) {
        ui->graphicsView->scale(1 / scaleFactor, 1 / scaleFactor);
        currentScale /= scaleFactor;
    }
}
