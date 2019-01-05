#include "antenne.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QtCore/qmath.h>

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


QString Antenne::getAntenneColor(){
    return color ;
}

qreal Antenne::ZoneRadius(){

    int c = 300000000;
    int alpha = 10;
    qreal lambda = c/this->getFrequence();
    //rapport signal sur bruit
    qreal rayonzone = qPow(((this->Pt*qPow(lambda,2))/this->Cmin),1/alpha);
    return rayonzone;
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
