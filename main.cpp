#include "gamescreen.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try {
        GameScreen w;
        w.show();
        return a.exec();

    }  catch (const std::exception& exc) {
        qDebug() << exc.what();
    }
}
