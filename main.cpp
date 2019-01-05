#include <QApplication>
#include "Game.h"
#include "antenne.h"
#include <QLabel>
#include <QPainter>

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Antenne* ant = new Antenne(2,"../placement/Antennes_info.txt");
    //ant->getId();
    //ant->showId();*/

    Antenne* ant = new Antenne();
    ant->getHighestPower("../placement/Antennes_info.txt");
    game = new Game();
    game->showMaximized();
    game->displayMainMenu();
    return a.exec();
}
