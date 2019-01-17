#ifndef ANTENNE_H
#define ANTENNE_H

#include "Hex.h"
#include <QPointF>
#include <string>

using namespace std;
/**
 * @brief
 *
 */
class Antenne
{
public:
    /**
     * @brief
     *
     */
    Antenne();
    /**
     * @brief
     *
     * @param id
     * @param Antennefile
     */
    Antenne(int id,QString Antennefile);
    /**
     * @brief
     *
     * @return int
     */
    int getId();
    /**
     * @brief
     *
     * @return double
     */
    double getPt();
    /**
     * @brief
     *
     * @return double
     */
    double getFrequence();
    /**
     * @brief
     *
     * @return QPointF
     */
    QPointF getPosition();
    /**
     * @brief
     *
     */
    void showId();
    /**
     * @brief
     *
     * @param file
     * @return double
     */
    double getHighestPower(QString file);
    /**
     * @brief
     *
     * @return QColor
     */
    QColor getAntenneColor();
    /**
     * @brief
     *
     * @return qreal
     */
    qreal ZoneRadius();
    /**
     * @brief
     *
     * @param a
     * @param pointAcalculer
     * @return double
     */
    double CalculerPuissanceRecue(Antenne *a,QPointF pointAcalculer);
    /**
     * @brief
     *
     * @param a
     * @param pointAcalculer
     * @param alphaMilieu
     * @param kMilieu
     * @return double
     */
    double getSpecialPuissanceRecue(Antenne *a,QPointF pointAcalculer, int alphaMilieu , int kMilieu);



    /**
     * @brief
     *
     * @param value
     */
    void setPosition(const QPointF &value);
    /**
     * @brief
     *
     * @param color
     * @return QColor
     */
    QColor colorFromString(string color);
    /**
     * @brief
     *
     * @return QColor
     */
    QColor getMaxPowerColor();
    /**
     * @brief
     *
     * @param Antennes
     * @return QColor
     */
    QColor getMaxPowerColor(QList<Antenne*> Antennes);

    /**
     * @brief
     *
     * @return QColor
     */
    QColor getColor() const;
    /**
     * @brief
     *
     * @param value
     */
    void setColor(const QColor &value);
    /**
     * @brief
     *
     * @param a
     * @param point
     * @return double
     */
    double calculerDistance(Antenne *a, QPointF point);
    /**
     * @brief
     *
     * @param a
     * @param h
     * @return bool
     */
    bool inRange(Antenne *a, Hex *h);
    /**
     * @brief
     *
     * @param antenne
     * @param obstacle
     * @param point
     * @return double
     */
    double Aligned(QPointF antenne, QPointF obstacle, QPointF point);

    /**
     * @brief
     *
     * @return QList<Hex *>
     */
    QList<Hex *> *getZone() const;
    /**
     * @brief
     *
     * @param value
     */
    void setZone(QList<Hex *> *value);
    QList<Hex *> *zone; /**< TODO: describe */


private:

    int id ; /**< TODO: describe */
    QPointF position; /**< TODO: describe */
    double Pt; /**< TODO: describe */
    double Frequence; /**< TODO: describe */
    QColor color; /**< TODO: describe */
    qreal Cmin; /**< TODO: describe */
};

#endif // ANTENNE_H


