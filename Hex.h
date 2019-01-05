#ifndef HEX_H
#define HEX_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>


class Hex: public QGraphicsPolygonItem{
public:
    // constructors
    Hex(QGraphicsItem* parent=NULL);
    // getters
    int getAttackOf(int side);
    bool getIsPlaced();
    QString getOwner();

    // event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void DrawOnClick(QGraphicsSceneMouseEvent *event);


    // setters
    void setAttackOf(int side, int attack);
    void setOwner(QString Antenne);
    void setIsPlaced(bool b);

    void displaySideAttacks();
    void createLines();
    void findNeighbors();


private:
    QList<QGraphicsLineItem*> lines;
    QList<Hex*> neighbors;
    bool isPlaced;
    QString owner;

};

#endif // HEX_H
