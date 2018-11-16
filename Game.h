#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "HexBoard.h"
#include "Hex.h"

class Game: public QGraphicsView{
public:
    // constructors
    Game(QWidget* parent= NULL );

    // public methods
    void start();

    // public attributes
    QGraphicsScene* scene;
    Hex *hex;
    HexBoard* hexBoard;

    QString whosTurn;
};

#endif // GAME_H
