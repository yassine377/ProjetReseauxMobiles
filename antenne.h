#ifndef ANTENNE_H
#define ANTENNE_H

#include "Hex.h"
#include <QPointF>


class Antenne
{
public:
    Antenne();
    Antenne(int id,QString Antennefile);
    int getId();
    double getPt();
    double getFrequence();
    QPointF getPosition();
    void showId();
    double getHighestPower(QString file);
    QString getAntenneColor();
    qreal ZoneRadius();


private:

    int id ;
    QPointF position;
    double Pt;
    double Frequence;
    QString color;
    QList<Hex* > zone ;
    qreal Cmin;
};

#endif // ANTENNE_H


