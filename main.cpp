#include <QApplication>
#include "Game.h"
#include "antenne.h"
#include <QLabel>
#include <QPainter>

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->showMaximized();
    game->displayMainMenu();




    return a.exec();
}
