#ifndef ANTENNE_H
#define ANTENNE_H

#include "Hex.h"
#include <QPointF>
#include <string>

using namespace std;

class Antenne
{
public:
    Antenne();
    Antenne(int id,QString Antennefile);
    int getId();
    double getPt();
    double getFrequence();
    QPointF getPosition();
    void setPt(double puissance=0);
    void showId();
    double getHighestPower(QString file);
    QColor getAntenneColor();
    qreal ZoneRadius();
    double CalculerPuissanceRecue(Antenne *a,QPointF pointAcalculer);
    double getSpecialPuissanceRecue(Antenne *a,QPointF pointAcalculer, int alphaMilieu , int kMilieu);



    void setPosition(const QPointF &value);
    QColor colorFromString(string color);
    QColor getMaxPowerColor();
    QColor getMaxPowerColor(QList<Antenne*> Antennes);

    QColor getColor() const;
    void setColor(const QColor &value);
    double calculerDistance(Antenne *a, QPointF point);
    bool inRange(Antenne *a, Hex *h);
    double Aligned(QPointF antenne, QPointF obstacle, QPointF point);

    QList<Hex *> *getZone() const;
    void setZone(QList<Hex *> *value);
    QList<Hex *> *zone;


private:

    int id ;
    QPointF position;
    double Pt;
    double Frequence;
    QColor color;
    qreal Cmin;
};

#endif // ANTENNE_H


