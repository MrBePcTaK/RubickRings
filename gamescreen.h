#ifndef GAMESCREEN_H
#define GAMESCREEN_H

// Qt
#include <QMainWindow>
#include <QGraphicsScene>
#include <memory>
#include <QDebug>
#include <QMessageBox>

// .H
#include "hungarianellipse.h"
#include "gameboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameScreen; }
QT_END_NAMESPACE

class GameScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr);
    ~GameScreen();

    void mousePressEvent(QMouseEvent *event) final;
    void wheelEvent(QWheelEvent *ZoomEvent) final;

public slots:
    void newGameBoard();
    void createGameBoard();
    void setGameBoard(GameBoard* scene);

    bool startGame();
    void about();

    void displayGameOverWindow();
    void setGameScreenInteractive(bool interactiveState);

signals:
    void gameOver();

private:
    Ui::GameScreen *ui;
    std::unique_ptr<GameBoard> m_gameScene;
};
#endif // GAMESCREEN_H
