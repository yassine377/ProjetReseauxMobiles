

#include "antenne.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QtCore/qmath.h>

#define ECHELLE 10
#define cstPuissance 100
#define vitessedeLumiere 299792458
#define PI 3.14159265358979323846
#define Gr 1
#define Gt 1
#define metres 1000
#define echelle 10000




/**
 * @brief constructeur Antenne pour la lecture de l'antenne dont l id est passe en argument
 *
 * @param id
 * @param Antennefile
 */
Antenne::Antenne(int id,QString Antennefile)
{

    QFile file(Antennefile);

    if(!file.open(QIODevice::ReadOnly |  QIODevice::Text))
        {
            qDebug() << " Could not open the Antenna's file ";
            return;
        }

    else {
        int Numline = 0;
        QTextStream in(&file);
              while (!in.atEnd())
              {
                if (Numline == id-1){
                   QString line = in.readLine();
                   QStringList data = line.split(';');
                   this->id=data.at(0).toInt();
                   this-> Pt =data.at(1).toDouble();
                   this->Frequence =data.at(2).toDouble();
                   this->color= data.at(3);
                   this->Cmin = data.at(4).toDouble();
                    }

                else {
                    in.readLine();
                }
              Numline++;
              }
              file.close();

    }

}

/**
 * @brief retourne id antenne
 *
 * @return int
 */
int Antenne::getId(){
    return id ;
}

/**
 * @brief retourne puissance antenne
 *
 * @return double
 */
double Antenne::getPt(){
    return Pt ;
}

/**
 * @brief retourne frequence antenne
 *
 * @return double
 */
double Antenne::getFrequence(){
    return Frequence ;
}

/**
 * @brief position antenne
 *
 * @return QPointF
 */
QPointF Antenne::getPosition(){
    return position ;
}



/**
 * @brief retourne couleur antenne
 *
 * @return QColor
 */
QColor Antenne::getAntenneColor(){
    return color ;
}



/**
 * @brief methode qui retourne le rayon de la zone de couverture de l antenne courante
 *
 * @return double
 */
double Antenne::ZoneRadius(){


    double alpha = 10;
    double lambda = vitessedeLumiere/this->Frequence;
    //rapport signal sur bruit
    double rayonzone = qPow(((this->Pt*qPow(lambda,2))/this->Cmin),1/alpha);
    /*
    QMessageBox msgBox;
    msgBox.setText(QString::number(rayonzone));
    msgBox.exec();*/
    return rayonzone *ECHELLE;
}

// methode qui retourne la puissance la plus elevé dans le fichier

/**
 * @brief
 *
 * @param afile
 * @return double
 */
double Antenne::getHighestPower(QString afile){
    QFile file(afile);
    QList<double> Pows ;

    if(!file.open(QIODevice::ReadOnly |  QIODevice::Text))
        {
            qDebug() << " Could not open the Antenna's file ";
            return 0;
        }

    else {
        int Numline = 0;
        QTextStream in(&file);
              while (!in.atEnd())
              {

                   QString line = in.readLine();
                   QStringList data = line.split(';');
                   this-> Pt =data.at(1).toDouble();
                   Pows.append(this->Pt);

              Numline++;
              }
              qSort(Pows.begin() , Pows.end());
              double max = Pows.last();
              file.close();
              /*QMessageBox msgBox;
              msgBox.setText(QString::number(max));
              msgBox.exec();*/
              return max;
    }


}

/**
 * @brief calculer la distance entre une antenne et un point
 *
 * @param a
 * @param point
 * @return double
 */
double Antenne::calculerDistance(Antenne *a, QPointF point){

    double distance=0;


    distance = sqrt(pow(a->getPosition().rx() - point.rx(),2)+ pow(a->getPosition().ry() - point.ry(),2));

    return distance+200;
}


/**
 * @brief calcule de la puissance recue suivant le model Free Space
 *
 * @param a
 * @param pointAcalculer
 * @return double
 */
double Antenne::CalculerPuissanceRecue(Antenne *a,QPointF pointAcalculer){

    double puissanceRecue = a->getPt() ;

    double lambda = vitessedeLumiere/a->getFrequence();
    double A = pow(lambda,2)/(4*PI*Gr);


        qDebug() << "A : "<<A << endl;
        double distance = 0.;
        distance = this->calculerDistance(a, pointAcalculer);

        qDebug() << "distance : " <<distance;

        if((distance ) != 0.)
            puissanceRecue = (a->getPt()*Gt*A / (4*PI*pow(distance*echelle,2)));

    qDebug() << puissanceRecue << endl;

    return puissanceRecue;
}

/**
 * @brief modifier la position de l'antenne
 *
 * @param value
 */
void Antenne::setPosition(const QPointF &value)
{
    position = value;
}



/**
 * @brief Calculer la puissance recue suivant la formule d'Okumura Hata-Cost
 *
 * @param a
 * @param pointAcalculer
 * @param alphaMilieu
 * @param kMilieu
 * @return double
 */
double Antenne::getSpecialPuissanceRecue(Antenne *a,QPointF pointAcalculer, int alphaMilieu , int kMilieu){

    double puissanceRecue = a->getPt() ;

    double lambda = vitessedeLumiere/a->getFrequence();
    double A = pow(lambda,2)/(4*PI*Gr);

        double distance = 0.;
        distance = this->calculerDistance(a, pointAcalculer);

        qDebug() << "distance : " <<distance;

        if((distance-200) != 0.)
                puissanceRecue = (a->getPt()*kMilieu*lambda / pow(distance*echelle,alphaMilieu));
    qDebug() << puissanceRecue << endl;

    return puissanceRecue;

}




/**
 * @brief
 *
 * @param color
 * @return QColor
 */
QColor Antenne::colorFromString(string color){

    if(color == "gray"){
        this->setColor(QColor(128,128,128));
    }
    else if(color == "red"){
        this->setColor(QColor(255,0,0));
    }
    else if(color == "green"){
        this->setColor(QColor(0,128,0));
    }
    else if (color == "yellow"){
        this->setColor(QColor(255,255,0));
    }
    else if(color == "blue"){
        this->setColor(QColor(0,0,255));
      }

    return this->getColor();
}

//

/**
 * @brief
 *
 * @param list
 * @return QColor
 */
QColor Antenne::getMaxPowerColor(QList<Antenne*> list)
{

        Antenne *an;
        QList<double> listDouble;

        an = list.at(0);
        double max = an->getPt();
        int j=1;
        for(int i=0;i<list.size()-1; i++){
            if(list.at(i)->getPt() > list.at(j++)->getPt()){

                max = list.at(i)->getPt();
                an = list.at(i);
            }
        }


    return an->getColor();
}

/**
 * @brief retourne la couleur de l'antenne
 *
 * @return QColor
 */
QColor Antenne::getColor() const
{
    return color;
}

/**
 * @brief modifier la couleur de l'antenne
 *
 * @param value
 */
void Antenne::setColor(const QColor &value)
{
    color = value;
}

/**
 * @brief tester si une maille appartient a la zone de couverture d une antenne
 *
 * @param a
 * @param h
 * @return bool
 */
bool Antenne::inRange(Antenne *a, Hex *h){

        //        qDebug() <<"Zone Radius : "<< a->ZoneRadius() << endl;
       // qDebug() <<"la distance : "<< a->calculerDistance(a, h->pos()) << endl;
       if(calculerDistance(a, h->pos()) <= a->ZoneRadius())
            return true;
        else
            return false;

}

/**
 * @brief retourne le rayon de la zone d une antenne
 *
 * @return QList<Hex *>
 */
QList<Hex *> *Antenne::getZone() const
{
    return zone;
}

/**
 * @brief modifie la zone
 *
 * @param value
 */
void Antenne::setZone(QList<Hex*> *value)
{
    zone = value;
}


/**
 * @brief teste si 3 points sont alignees
 *
 * @param antenne
 * @param obstacle
 * @param point
 * @return double
 */
double Antenne::Aligned(QPointF antenne, QPointF obstacle, QPointF point){

    return (antenne.rx() * (obstacle.ry() - point.ry()) + obstacle.x() * (point.ry() - antenne.ry()) + point.rx() * (antenne.rx() - obstacle.ry()));

}
