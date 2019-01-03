#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "HexBoard.h"
#include <QMouseEvent>
#include "antenne.h"


class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods
    void displayMainMenu();
    QString getWhosTurn();
    void setWhosTurn(QString Antenne);
    void pickUpCard(Hex* card);
    void placeCard(Hex* hexToReplace);
    void nextAntennesTurn();
    void removeFromDeck(Hex* card,QString Antenne);
    void TestAllPlacedAndInitalizeColor();

    // events
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);

    // public attributes
    QGraphicsScene* scene;
    HexBoard* hexBoard;
    Hex* cardToPlace;
    QPointF originalPos;

public slots:
    void start();
    void clickedSlot();

private:
    // private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewCard(QString Antenne,int id);
    void createInitialCards();
    void drawCards();

    // private attributes
    QString whosTurn_;
    QGraphicsTextItem* whosTurnText;
    QList<Hex* > AntenneItem;
    QList<Antenne* > AntenneInfo;
};

#endif // GAME_H
