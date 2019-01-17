#include "Hex.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QBrush>
#include "Game.h"
#include "antenne.h"
#include <QTextCursor>

extern Game* game;

#include <QDebug> // TODO remove
Hex::Hex(QGraphicsItem *parent){


    setAcceptHoverEvents(true);
    // draw the polygon

    // points needed to draw hexagon: (1,0), (2,0), (3,1), (2,2), (1,2), (0,1)
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(2,2)
              << QPointF(1,2) << QPointF(0,1);

    // scale the points
    int SCALE_BY = 40;
    for (size_t i = 0, n = hexPoints.size(); i < n; ++i){
        hexPoints[i] = hexPoints[i] * SCALE_BY;
    }

    // create a polygon with the scaled points
    QPolygonF hexagon(hexPoints);

    // draw the poly
    setPolygon(hexagon);

    // initialize
    isPlaced = false;


}

bool Hex::getIsPlaced(){
    return isPlaced;
}

QString Hex::getOwner(){
    return owner;
}

void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // if this hex is NOT placed (so it is a card) then pick it up
    if (getIsPlaced() == false){
        game->pickUpCard(this);
    }

    // if this hex IS placed, then replace it
    else {
        game->placeCard(this);
    }
}





void Hex::setOwner(QString Nature){
    // set the owner
    owner = Nature;

    // change the color
    if (Nature == QString("NOONE")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::lightGray);
        setBrush(brush);
    }

    if (Nature == QString("Antenne")){

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        QImage antenne = QImage("../placement/antenne.png","png");
        brush.setTextureImage(antenne);
        setBrush(brush);
    }

    if (Nature == QString("Immeuble")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        QImage immeuble = QImage("../placement/immeuble.jpg","jpg");
        brush.setTextureImage(immeuble);
        setBrush(brush);
    }



}

void Hex::setIsPlaced(bool b){
    isPlaced = b;
}



void Hex::createLines(){
    QPointF hexCenter(x()+10,y()+40);
    QPointF finalPt(hexCenter.x(),hexCenter.y()-65);
    QLineF ln(hexCenter,finalPt);

    for (size_t i = 0, n = 6; i < n; ++i){
        QLineF lnCopy(ln);
        lnCopy.setAngle(90+60*i);
        QGraphicsLineItem* line = new QGraphicsLineItem(lnCopy,this);
        lines.append(line);
        line->setVisible(false);
    }
}

void Hex::findNeighbors(){
    for (size_t i = 0, n = lines.size(); i < n; i++){
        // if the line collides with an item of type Hex, add it to neighbors
        QList<QGraphicsItem*> cItems = lines[i]->collidingItems();
        for (size_t j = 0; j < cItems.size(); j++){
            Hex* item = dynamic_cast<Hex*>(cItems[j]);
            if (cItems[j] != this && item){
                neighbors.append(item);
            }
        }
    }
}

double Hex::getPuissanceRecue() const
{
    return PuissanceRecue;
}

void Hex::setPuissanceRecue(double value)
{
    PuissanceRecue = value;
}

void Hex::hoverEnterEvent(QGraphicsSceneHoverEvent *event){

            setToolTip(QString::number(this->getPuissanceRecue()));

}

void Hex::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){



}
