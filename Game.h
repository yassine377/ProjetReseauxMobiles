#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "HexBoard.h"
#include <QMouseEvent>
#include "antenne.h"
#include <QGraphicsView>


/**
 * @brief
 *
 */
class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    /**
     * @brief
     *
     * @param parent
     */
    Game(QWidget* parent=NULL);

    // public methods

    //static Game* getInstance();

    /**
     * @brief
     *
     */
    void displayMainMenu();
    /**
     * @brief
     *
     * @return QString
     */
    QString getWhosTurn();
    /**
     * @brief
     *
     * @param Antenne
     */
    void setWhosTurn(QString Antenne);
    /**
     * @brief
     *
     * @param card
     */
    void pickUpCard(Hex* card);
    /**
     * @brief
     *
     * @param hexToReplace
     */
    void placeCard(Hex *hexToReplace);
    /**
     * @brief
     *
     */
    void nextAntennesTurn();
    /**
     * @brief
     *
     * @param card
     * @param Antenne
     */
    void removeFromDeck(Hex* card,QString Antenne);
    /**
     * @brief
     *
     */
    void TestAllPlacedAndInitalizeColor();
    /**
     * @brief
     *
     */
    void ouvrirDocument();


    //void drawcercle();

    // events
    /**
     * @brief
     *
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);
    /**
     * @brief
     *
     * @param event
     */
    void mousePressEvent(QMouseEvent* event);


    // public attributes
    QGraphicsScene* scene; /**< TODO: describe */
    HexBoard* hexBoard; /**< TODO: describe */
    Hex* cardToPlace; /**< TODO: describe */
    QPointF originalPos; /**< TODO: describe */
    QList<QPointF > positions ; /**< TODO: describe */

public slots:
    /**
     * @brief
     *
     */
    void start();
    /**
     * @brief
     *
     */
    void clickedSlot();

private:
    // private methods
   // Game(QWidget* parent=NULL);
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
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    /**
     * @brief
     *
     */
    void drawGUI();
    /**
     * @brief
     *
     * @param Antenne
     * @param id
     */
    void createNewCard(QString Antenne,int id);
    /**
     * @brief
     *
     */
    void createInitialCards();
    /**
     * @brief
     *
     */
    void drawCards();


    // private attributes
    static Game* instance; /**< TODO: describe */
    QString whosTurn_; /**< TODO: describe */
    QGraphicsTextItem* whosTurnText; /**< TODO: describe */
    QList<Hex* > AntenneItem; /**< TODO: describe */
    QList<Antenne* > AntenneInfo; /**< TODO: describe */
    QList<Hex*> Immeubles; /**< TODO: describe */
};

#endif // GAME_H
