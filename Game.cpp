#include "Game.h"
#include "HexBoard.h"
#include "Hex.h"

Game::Game(QWidget *parent){
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,780);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,0,0);
    setScene(scene);
}

void Game::start(){
    // test code TODO remove
    hexBoard = new HexBoard();
    hexBoard->placeHexes(100,100,12,9);

}
