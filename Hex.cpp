#include "Hex.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QBrush>
#include "Game.h"
#include "antenne.h"

extern Game* game; /**< TODO: game variable */

#include <QDebug> // TODO remove
/**
 * @brief
 *
 * @param parent
 */
Hex::Hex(QGraphicsItem *parent){
    /// \brief draw the polygon

    /// \brief points needed to draw hexagon: (1,0), (2,0), (3,1), (2,2), (1,2), (0,1)
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(2,2)
              << QPointF(1,2) << QPointF(0,1);

    /// \brief scale the points
    int SCALE_BY = 40;
    for (size_t i = 0, n = hexPoints.size(); i < n; ++i){
        hexPoints[i] = hexPoints[i] * SCALE_BY;
    }

    /// \brief create a polygon with the scaled points
    QPolygonF hexagon(hexPoints);

    /// \brief draw the poly
    setPolygon(hexagon);

    /// \brief initialize
    isPlaced = false;


}

/**
 * @brief
 *
 * @return bool
 */
bool Hex::getIsPlaced(){
    return isPlaced;
}

/**
 * @brief retourne la nature de la maille
 *
 * @return QString
 */
QString Hex::getOwner(){
    return owner;
}

/**
 * @brief methode pour creer un evenement
 * clique sur QGraphicItem (Hex)
 *
 * @param event
 */
void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event){
    /// \brief if this hex is NOT placed (so it is a card) then pick it up
    if (getIsPlaced() == false){
        game->pickUpCard(this);
    }

    /// \brief if this hex IS placed, then replace it
    else {
        game->placeCard(this);
    }
}





/**
 * @brief modifie la nature de Hex (maille)
 * "NOONE" maille vide
 * "Antenne" contient une antenne
 * "Immeuble" contient un obstacle
 * afficher icone antenne
 * afficher icone immeuble
 *
 * @param Nature
 */
void Hex::setOwner(QString Nature){
    /// \brief set the owner
    owner = Nature;

    /// \brief change the color
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

/**
 * @brief retourner un boolean
 * teste si card placee ou non
 *
 * @param b
 */
void Hex::setIsPlaced(bool b){
    isPlaced = b;
}



/**
 * @brief dessiner les lignes de la maille
 *
 */
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



/**
 * @brief methode retourne la puissance recue de la maille
 *
 * @return double
 */
double Hex::getPuissanceRecue() const
{
    return PuissanceRecue;
}

/**
 * @brief methode modifie la puissance recue
 *
 * @param value
 */
void Hex::setPuissanceRecue(double value)
{
    PuissanceRecue = value;
}
