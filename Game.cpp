#include "Game.h"
#include "HexBoard.h"
#include "Button.h"
#include <QGraphicsTextItem>
#include <stdlib.h> // srand() and rand()
#include <time.h> // time()
#include <QMessageBox>
#include <QPushButton>
#include <QPainter>
#include <QTextCursor>
#include <QRadialGradient>
#include <iostream>
#include<Windows.h>
#include <QTimeLine>
#include <QDebug>

using namespace std;



/**
 * @brief constructeur create QGraphicScene
 *
 * @param parent
 */
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


/**
 * @brief cette methode commence la simulation avec la creation
 * du HexBoard , place les mailles hecagonales et cree les antennes
 * a placer ainsi que les obstacles .
 *
 */
void Game::start(){
    /// clear the screen
    scene->clear();

    /// test code TODO remove
    hexBoard = new HexBoard();
    hexBoard->placeHexes(140,10,11,10);
    drawGUI();
    createInitialCards();

    for (size_t i = 0; i < 3; i++){
        Hex* immeuble = new Hex();
        immeuble->setOwner("Immeuble");
        Immeubles.append(immeuble);
    }
    Immeubles[0]->setPos(304,174);

    scene->addItem(Immeubles[0]);

    Immeubles[1]->setPos(140,420);
    scene->addItem(Immeubles[1]);
    Immeubles[2]->setPos(632,502);
    scene->addItem(Immeubles[2]);
}

/**
 * @brief
 *
 * @param x
 * @param y
 * @param width
 * @param height
 * @param color
 * @param opacity
 */
void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    /// draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

/**
 * @brief cette methode dessine le panneau qui contient les antennes
 * a placer et l'ajoute a la scene
 * et met les antennes dans le panneau
 *
 */
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



/**
 * @brief methode appelee au clic du bouton reinitialize
 * appel methode start
 * vider les listes AntenneItem, AntenneInfo et positions
 *
 */
void Game::clickedSlot(){
    this->start();
    AntenneItem.clear();
    AntenneInfo.clear();
    positions.clear();
}

/**
 * @brief methode qui ouvre le pdf du manuel d utilisation
 * de l'application.
 *
 */
void Game::ouvrirDocument()
{

   ShellExecuteA(NULL,"open",  "..\Rapport Framework Flou.pdf",0,0,SW_NORMAL);
}

/**
 * @brief methode cree le menu principal de l'application
 * 3 boutons  Simulation , Guide d'utilisation , Quitter
 *
 */
void Game::displayMainMenu(){
       /// create the title text
        QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Mobil Network Simulation APP"));
        QFont titleFont("comic sans",50);
        titleText->setFont(titleFont);
        int txPos = this->width()/2 - titleText->boundingRect().width()/2;
        int tyPos = 150;
        titleText->setPos(txPos,tyPos);
        scene->addItem(titleText);

        /// create the play button
           Button* playButton = new Button(QString("Simulation"));
           int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
           int byPos = 275;
           playButton->setPos(bxPos,byPos);
           connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
           scene->addItem(playButton);

           /// create the quit button
           Button* quitButton = new Button(QString("Quitter"));
               int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
               int qyPos = 430;
               quitButton->setPos(qxPos,qyPos);
               connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
               scene->addItem(quitButton);


               /// create the quit button
                   Button* manuButton = new Button(QString("Guide d'utilisation"));
                   int mqxPos = this->width()/2 - manuButton->boundingRect().width()/2;
                   int mqyPos = 350;
                   manuButton->setPos(mqxPos,mqyPos);
                   connect(manuButton,SIGNAL(clicked()),this,SLOT(ouvrirDocument()));
                   scene->addItem(manuButton);


}

/**
 * @brief
 *
 * @param antenne
 * @param id
 */
void Game::createNewCard(QString antenne, int id){
    /// create the card
    Hex* card = new Hex();
    card->setOwner(antenne);
    card->setIsPlaced(false);

    /// add the card to the proper list
    if (antenne == QString("Antenne")){
        AntenneItem.append(card);
    }

    /// draw the cards
    drawCards();
}

/**
 * @brief methode pour creer les antennes initiales sur la panneau
 * appel createNewCard dans 5 iterations .
 * appel drawCards pour dessiner les antennes creée
 *
 */
void Game::createInitialCards(){
    // create antenne cards
    for (size_t i = 1, n = 6; i < n; i++){
        createNewCard(QString("Antenne"),i);
    }

    drawCards();
}

/**
 * @brief methode dessine les antennes initiales
 * liste AntenneItem de type QGraphicItem contient
 * les antennes de depart
 * positions des antennes
 *
 */
void Game::drawCards(){
    /// remove all of Antennes cards from the scene
    for (size_t i = 0, n = AntenneItem.size(); i < n; i++){
        scene->removeItem(AntenneItem[i]);
    }

    /// draw Antennes cards

    for (size_t i = 0, n = AntenneItem.size(); i < n; i++){
        Hex* card = AntenneItem[i];
        card->setPos(-45,40+85*i);
        scene->addItem(card);
    }
}




QString Game::getWhosTurn(){
    return whosTurn_;
}

/**
 * @brief
 *
 * @param antenne
 */
void Game::setWhosTurn(QString antenne){
    /// change the QString
    whosTurn_ = antenne;

    /// change the QGraphicsTextItem
    whosTurnText->setPlainText(QString("Whos turn: ") + antenne);
}

/**
 * @brief methode differencie antenne placee
 * et antenne initiale (card)
 *pour deplacer que les card
 *
 * @param card
 */
void Game::pickUpCard(Hex *card){

    /// picks up the specified card
    if (card->getOwner() == getWhosTurn() && cardToPlace == NULL){
        cardToPlace = card;
            originalPos = card->pos();
        return;
}
}


/**
 * @brief methode pour plusieurs action sur la scene
 * 1. deplacement antenne initiale vers maille "NOONE"
 * 2. enregistrer chaque antenne dans AntenneInfo
 * 3. afficher les informations de l'antenne placee
 * 4. afficher la zone de couverture avec graduation de la couleur
 * 5. teste si l'antenne suivante est placee sur une maille
 * contenant deja une antenne
 * 6. lecture puissance recue sur les maille de la zone de couverture
 *
 *
 * @param hexToReplace
 */
void Game::placeCard(Hex *hexToReplace){

    /// replaces the specified hex with the cardToPlace
    if(cardToPlace)
    {

    cardToPlace->setPos(hexToReplace->pos());
    hexToReplace->setOwner("Antenne");
    positions.append(hexToReplace->pos());

    Antenne* ant = new Antenne (positions.indexOf(hexToReplace->pos())+1 , "../placement/Antennes_info.txt");
    ant->setPosition(hexToReplace->pos());
    AntenneInfo.append(ant);
    QGraphicsTextItem* info = new QGraphicsTextItem();
    info->setTextInteractionFlags(Qt::TextEditorInteraction);
    double x = hexToReplace->pos().rx()+80;
    double y = hexToReplace->pos().ry()+50;
    info->setPos(x,y);
    info->setDefaultTextColor(Qt::darkRed);
    QFont serifFont("Times", 10, QFont::Bold);
    info->setFont(serifFont);
    QTextDocument* doc = info->document();
    scene->addItem(info);
    QTextCursor cursor(doc);
    cursor.beginEditBlock();
    cursor.insertText("Position : ("+QString::number(positions.last().rx())+","+ QString::number(positions.last().ry()) + ") \n");
    cursor.insertText("Id : " + QString::number(AntenneInfo.last()->getId()) + "\n");
    cursor.insertText("Frequence : " + QString::number(AntenneInfo.last()->getFrequence()) +"\n");
    cursor.insertText("Puissance :" +QString::number(AntenneInfo.last()->getPt())+"\n");
    cursor.endEditBlock();


    /// \brief definir r,g,b de la couleur de l antenne

    int r = ant->getColor().toRgb().red() ;
    int g = ant->getColor().toRgb().green() ;
    int b = ant->getColor().toRgb().blue() ;

    ///  \brief  dessiner les cercles de la zone de couverture

    for (int diameter = 0; diameter <AntenneInfo.last()->ZoneRadius(); diameter += 3.7)

    {

        QGraphicsEllipseItem *orbit = new QGraphicsEllipseItem(hexToReplace->pos().rx()+60-diameter / 2, hexToReplace->pos().ry()+40-diameter / 2, diameter, diameter);

        ///  \brief eclaircir la couleur avec rgb en s eloignant de la maille antenne

        r = r + (((0.0035*diameter)/130)*(255-ant->getColor().toRgb().red()));
        g = g + (((0.0045*diameter)/130)*(255-ant->getColor().toRgb().green()));
        b = b + (((0.0065*diameter)/200)*(255-ant->getColor().toRgb().blue()));

        ///  \brief dessiner et colorier les cercles

        orbit->setPen(QColor(r,g,b));
        scene->addItem(orbit);

    }

    hexBoard->getHexes().removeAll(hexToReplace);
    hexBoard->getHexes().append(cardToPlace);
    scene->removeItem(hexToReplace);
    cardToPlace->setIsPlaced(true);
    removeFromDeck(cardToPlace,getWhosTurn());
    cardToPlace = NULL;

    ant->zone = new QList<Hex*>();

    for (int i=0; i< hexBoard->getHexes().size(); i++) {


        if(ant->inRange(ant, hexBoard->getHexes().at(i))){

                ant->getZone()->append(hexBoard->getHexes().at(i));

        }

    }

    int i=0;

    for (Hex *h: *ant->getZone()) {
            for(Hex *obstacle : Immeubles){

                if(h->pos() != obstacle->pos() && h->getOwner() != "Antenne"){
                    h->setPuissanceRecue(ant->CalculerPuissanceRecue(ant,h->pos()));
                }
                else  if(ant->Aligned(ant->getPosition(), obstacle->pos(), h->pos())== 0.){
                    h->setPuissanceRecue(ant->getSpecialPuissanceRecue(ant, h->pos(), 4,50));
                    break;
                }

            }

            qDebug() << h->getOwner() << endl;
            QGraphicsTextItem* info = new QGraphicsTextItem();
            info->setTextInteractionFlags(Qt::TextEditorInteraction);
            info->setPos(h->pos());
            info->setDefaultTextColor(Qt::white);
            QFont serifFont("Times", 10, QFont::Bold);
            info->setFont(serifFont);
            QTextDocument* doc = info->document();
            scene->addItem(info);
            QTextCursor cursor(doc);
            cursor.beginEditBlock();
            cursor.insertText("Puissance :" +QString::number(h->getPuissanceRecue()) +"\n");
            cursor.endEditBlock();




    }


    }
}



/**
 * @brief methode enleve l'antenne initial pour deplacement
 *
 * @param card
 * @param antenne
 */
void Game::removeFromDeck(Hex *card, QString antenne){
    if (antenne == QString("Antenne")){

        AntenneItem.removeAll(card);
    }
}

/**
 * @brief faire suivre l antenne a la souris
 *
 * @param event
 */
void Game::mouseMoveEvent(QMouseEvent *event){

    /// \brief if there is a cardToPlace, then make it follow the mouse

    if (cardToPlace){
        cardToPlace->setPos(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

/**
 * @brief
 *
 * @param event
 */
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

