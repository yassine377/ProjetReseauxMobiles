#include <QApplication>
#include "Game.h"
#include "antenne.h"
#include <QLabel>
#include <QPainter>

Game* game; /**< TODO: game variable */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
   // Game* game=Game::getInstance();
    game->showMaximized();
    //game->showFullScreen();
    game->displayMainMenu();
    return a.exec();
}
