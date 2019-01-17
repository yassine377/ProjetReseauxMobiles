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


Antenne::Antenne()
{}

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
                   this->Pt =data.at(1).toDouble();
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

int Antenne::getId(){
    return id ;
}

double Antenne::getPt(){
    return Pt ;
}

double Antenne::getFrequence(){
    return Frequence ;
}

QPointF Antenne::getPosition(){
    return position ;
}

void Antenne::showId(){
    QMessageBox msgBox;
    msgBox.setText(QString::number(id));
    msgBox.exec();
}


QColor Antenne::getAntenneColor(){
    return color ;
}

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

double Antenne::calculerDistance(Antenne *a, QPointF point){

    double distance=0;


    distance = sqrt(pow(a->getPosition().rx() - point.rx(),2)+ pow(a->getPosition().ry() - point.ry(),2));

    return distance+200;
}

double Antenne::CalculerPuissanceRecue(Antenne *a,QPointF pointAcalculer){

    double puissanceRecue = a->getPt() ;

    double lambda = vitessedeLumiere/a->getFrequence();
    double A = pow(lambda,2)/(4*PI*Gr);


        qDebug() << "A : "<<A << endl;
        double distance = 0.;
        distance = this->calculerDistance(a, pointAcalculer);

        qDebug() << "distance : " <<distance;

        if((distance -200) != 0.)
            puissanceRecue = (a->getPt()*Gt*A / (4*PI*pow(distance*echelle,2)));

    qDebug() << puissanceRecue << endl;

    return puissanceRecue;
}

void Antenne::setPosition(const QPointF &value)
{
    position = value;
}


QColor Antenne::getMaxPowerColor(){

        double maxPower;
        maxPower = getHighestPower("../placement/Antennes_info.txt");

        QFile file("../placement/Antennes_info.txt");

        if(!file.open(QIODevice::ReadOnly |  QIODevice::Text))
            {
                qDebug() << " Could not open the Antenna's file ";
                return nullptr;
            }
        else {
            int Numline = 0;
            QTextStream in(&file);
                  while (!in.atEnd())
                  {

                       QString line = in.readLine();
                       QStringList data = line.split(';');
                       if(data.at(1).toDouble() == maxPower ){
                           this->id = std::stoi( data.at(0).toStdString() ) ;
                           this->Pt = data.at(1).toDouble();
                           this->Frequence = data.at(2).toDouble();
                           this->color = colorFromString(data.at(3).toStdString());
                       }

                    Numline++;
                  }

             file.close();

                  return this->getColor();
        }


}

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

QColor Antenne::getColor() const
{
    return color;
}

void Antenne::setColor(const QColor &value)
{
    color = value;
}

bool Antenne::inRange(Antenne *a, Hex *h){

        //        qDebug() <<"Zone Radius : "<< a->ZoneRadius() << endl;
       // qDebug() <<"la distance : "<< a->calculerDistance(a, h->pos()) << endl;
       if(calculerDistance(a, h->pos()) <= a->ZoneRadius())
            return true;
        else
            return false;

}

QList<Hex *> *Antenne::getZone() const
{
    return zone;
}

void Antenne::setZone(QList<Hex*> *value)
{
    zone = value;
}

//Formule d'Okumura Hata-Cost

double Antenne::getSpecialPuissanceRecue(Antenne *a,QPointF pointAcalculer, int alphaMilieu , int kMilieu){

    double puissanceRecue = a->getPt() ;

    double lambda = vitessedeLumiere/a->getFrequence();
    double A = pow(lambda,2)/(4*PI*Gr);

        double distance = 0.;
        distance = this->calculerDistance(a, pointAcalculer);

        qDebug() << "distance : " <<distance;

        if((distance-200) != 0.)
                puissanceRecue = (a->getPt()*kMilieu*lambda*2 / pow(distance,alphaMilieu));

        qDebug() << puissanceRecue << endl;


    return puissanceRecue;

}

double Antenne::Aligned(QPointF antenne, QPointF obstacle, QPointF point){

    return (antenne.rx() * (obstacle.ry() - point.ry()) + obstacle.rx() * (point.ry() - antenne.ry()) + point.rx() * (antenne.ry() - obstacle.ry()));

}


void Antenne::setPt(double puissance){
        this->Pt = puissance;
}
