#include "HexBoard.h"
#include "Game.h"
#include <iostream>

extern Game* game;

using namespace std;

HexBoard::HexBoard(){

}

QList<Hex *> HexBoard::getHexes(){
    return hexes;
}

void HexBoard::placeHexes(int x, int y, int cols, int rows){
    int X_SHIFT = 82;
    int Y_SHIFT = 41;

    for (size_t i = 0, n = cols; i < n; i++){
        if (i % 2 == 0){ // even column
            Y_SHIFT = 0;
        }
        else{ // odd column
            Y_SHIFT = 41;
        }
        createHexColumn(x+X_SHIFT*i,y+Y_SHIFT,rows);


    }
}

void HexBoard::createHexColumn(int x, int y, int numOfRows){
    // creates a column of Hexes at the specified location with the specified
    // number of rows
    for (size_t i = 0, n = numOfRows; i < n; i++){
        Hex* hex = new Hex();
        hex->setPos(x,y+82*i);

          std::cout << hex->getCentroid().x() <<endl;
          std::cout << hex->getCentroid().y() <<endl;

          QRectF rect(hex->getCentroid().x(),hex->getCentroid().y(), 40.0,40.0);


          game->scene->addEllipse(rect);

        game->scene->addItem(hex);
    }
}
