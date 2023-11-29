#include "compteur.h"
#include "ui_compteur.h"
#include <QApplication>
#include <QObject>
#include <QPushButton>
#include <QWidget>
compteur::compteur():mag_(0),res_(0)
{

}
int compteur::getMag(){
    return mag_;
}
int compteur::getRes(){
    return res_;
}
void compteur::augmenterMag(){
    mag_++;
    emit envoyerMag(mag_);
}
void compteur::augmenterRes(){
    res_++;
    emit envoyerRes(res_);
}
void compteur::decrementerMag(){
    if(mag_==0){
        qInfo() << "La quantité d'un produit ne peut être négative.";
        mag_==0;
    }
    else{
    mag_--;
    }
    emit envoyerMag(mag_);
}
void compteur::decrementerRes(){
    if(res_==0){
        qInfo() << "La quantité d'un produit ne peut être négative.";
        res_==0;
    }
    else{
    res_--;
    }
    emit envoyerRes(res_);
}
