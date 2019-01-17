#include "HexBoard.h"
#include "Game.h"

extern Game* game; /**< TODO: describe */

/**
 * @brief constructeur HexBoard
 *
 */
HexBoard::HexBoard(){

}

/**
 * @brief retourne les mailles du HexBoard
 *
 * @return QList<Hex *>
 */
QList<Hex *> HexBoard::getHexes(){
    return hexes;
}

/**
 * @brief placer les hexagones dans le HexBoard
 * translate avec SHIFT sur chaque colonne dessinee
 *
 * @param x
 * @param y
 * @param cols
 * @param rows
 */
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

/**
 * @brief methode cree une colonne de mailles hexagone
 *
 * @param x
 * @param y
 * @param numOfRows
 */
void HexBoard::createHexColumn(int x, int y, int numOfRows){
    // creates a column of Hexes at the specified location with the specified
    // number of rows
    for (size_t i = 0, n = numOfRows; i < n; i++){
        Hex* hex = new Hex();
        hex->setPos(x,y+82*i);
        hexes.append(hex);
        game->scene->addItem(hex);

        // initialize
        hex->setOwner(QString("NOONE"));
        hex->setIsPlaced(true);
    }
}
