#ifndef ANTENNE_H
#define ANTENNE_H

#include <QGraphicsPolygonItem>

class Antenne : public QGraphicsPolygonItem
{
public:
    Antenne(QGraphicsItem* parent=NULL);


private:
    QString nom;
    int position;
    int puissance;
    int frequence;



};

#endif // ANTENNE_H
