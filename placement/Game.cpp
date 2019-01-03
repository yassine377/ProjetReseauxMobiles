#include "Game.h"
#include "HexBoard.h"
#include "Button.h"
#include <QGraphicsTextItem>
#include <stdlib.h> // srand() and rand()
#include <time.h> // time()
#include <QMessageBox>
#include <QPushButton>
#include <QPainter>


#include <QDebug>
Game::Game(QWidget *parent){
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1125,850);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,900);
    setScene(scene);
    QPushButton *button = new QPushButton("Reinitialiser",this);
    button->setGeometry(QRect(QPoint(5, 800),QSize(120, 30)));
    connect(button, SIGNAL (released()), this, SLOT (clickedSlot()));

    // initialize
    cardToPlace = NULL;
}

void Game::start(){
    // clear the screen
    scene->clear();

    // test code TODO remove
    hexBoard = new HexBoard();
    hexBoard->placeHexes(140,10,11,10);
    drawGUI();
    createInitialCards();
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}
/*
void Game::TestAllPlacedAndInitalizeColor(){

    if (AntenneItem.size()==4  && cardToPlace==NULL){
        Antenne* a = new Antenne();
        double P = a->getHighestPower("../placement/Antennes_info.txt");



    }

}*/
void Game::drawGUI(){
    // draw the left panel
    drawPanel(-45,35,120,820,Qt::darkRed,1);

    // place antenne 1 text
    QGraphicsTextItem* p1 = new QGraphicsTextItem("Antenne");
    p1->setPos(25,0);
    scene->addItem(p1);

    // place whosTurnText
    whosTurnText = new QGraphicsTextItem();
    setWhosTurn(QString("Antenne"));
    whosTurnText->setPos(490,0);
}

void Game::clickedSlot(){
    this->start();
    AntenneItem.clear();
}


void Game::createNewCard(QString antenne, int id){
    // create the card
    Hex* card = new Hex();
    Antenne* ant = new Antenne (id , "../placement/Antennes_info.txt");
    card->setOwner(antenne);
    card->setIsPlaced(false);

    // add the card to the proper list
    if (antenne == QString("Antenne")){
        AntenneItem.append(card);
        AntenneInfo.append(ant);
    }

    // draw the cards
    drawCards();
}

void Game::createInitialCards(){
    // create antenne cards
    for (size_t i = 1, n = 6; i < n; i++){
        createNewCard(QString("Antenne"),i);
    }

    drawCards();
}

void Game::drawCards(){
    // remove all of Antennes cards from the scene
    for (size_t i = 0, n = AntenneItem.size(); i < n; i++){
        scene->removeItem(AntenneItem[i]);
    }

    // draw Antennes cards

    for (size_t i = 0, n = AntenneItem.size(); i < n; i++){
        Hex* card = AntenneItem[i];
        card->setPos(-45,40+85*i);
        scene->addItem(card);
        }
}


void Game::displayMainMenu(){
    start();
}

QString Game::getWhosTurn(){
    return whosTurn_;
}

void Game::setWhosTurn(QString antenne){
    // change the QString
    whosTurn_ = antenne;

    // change the QGraphicsTextItem
    whosTurnText->setPlainText(QString("Whos turn: ") + antenne);
}

void Game::pickUpCard(Hex *card){
    // picks up the specified card
    if (card->getOwner() == getWhosTurn() && cardToPlace == NULL){
        cardToPlace = card;
        originalPos = card->pos();
        return;
}
}

void Game::placeCard(Hex *hexToReplace){

    // replaces the specified hex with the cardToPlace
    if(cardToPlace)
    {
    cardToPlace->setPos(hexToReplace->pos());
    hexBoard->getHexes().removeAll(hexToReplace);
    hexBoard->getHexes().append(cardToPlace);
    scene->removeItem(hexToReplace);
    cardToPlace->setIsPlaced(true);
    removeFromDeck(cardToPlace,getWhosTurn());
    cardToPlace = NULL;

    // replace the placed card w a new one
    //createNewCard(getWhosTurn());
    }
}



void Game::removeFromDeck(Hex *card, QString antenne){
    if (antenne == QString("Antenne")){

        AntenneItem.removeAll(card);
    }
}

void Game::mouseMoveEvent(QMouseEvent *event){
    // if there is a cardToPlace, then make it follow the mouse
    if (cardToPlace){
        cardToPlace->setPos(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
    // make right click return cardToPlace to originalPos
    if (event->button() == Qt::RightButton){
        if (cardToPlace){
            cardToPlace->setPos(originalPos);
            cardToPlace = NULL;
            return;
        }
    }

    QGraphicsView::mousePressEvent(event);
}



