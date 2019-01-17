#ifndef HEX_H
#define HEX_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>


/**
 * @brief
 *
 */
class Hex: public QGraphicsPolygonItem{
public:
    // constructors
    /**
     * @brief
     *
     * @param parent
     */
    Hex(QGraphicsItem* parent=NULL);
    // getters
    /**
     * @brief
     *
     * @param side
     * @return int
     */
    int getAttackOf(int side);
    /**
     * @brief
     *
     * @return bool
     */
    bool getIsPlaced();
    /**
     * @brief
     *
     * @return QString
     */
    QString getOwner();

    // event
    /**
     * @brief
     *
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    /**
     * @brief
     *
     * @param event
     */
    void DrawOnClick(QGraphicsSceneMouseEvent *event);


    // setters
    /**
     * @brief
     *
     * @param side
     * @param attack
     */
    void setAttackOf(int side, int attack);
    /**
     * @brief
     *
     * @param Antenne
     */
    void setOwner(QString Antenne);
    /**
     * @brief
     *
     * @param b
     */
    void setIsPlaced(bool b);

    /**
     * @brief
     *
     */
    void displaySideAttacks();
    /**
     * @brief
     *
     */
    void createLines();
    /**
     * @brief
     *
     */
    void findNeighbors();


    /**
     * @brief
     *
     * @return double
     */
    double getPuissanceRecue() const;
    /**
     * @brief
     *
     * @param value
     */
    void setPuissanceRecue(double value);
    double PuissanceRecue; /**< TODO: describe */


private:
    QList<QGraphicsLineItem*> lines; /**< TODO: describe */
    QList<Hex*> neighbors; /**< TODO: describe */
    bool isPlaced; /**< TODO: describe */
    QString owner; /**< TODO: describe */

};

#endif // HEX_H
