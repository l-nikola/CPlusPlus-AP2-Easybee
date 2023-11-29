#include "compteurentrepot.h"
#include "ui_compteurentrepot.h"
#include <QApplication>
#include <QObject>
#include <QPushButton>
#include <QWidget>
compteurEntrepot::compteurEntrepot():entrepot_(0)
{

}
int compteurEntrepot::getEntrepot(){
    return entrepot_;
}
void compteurEntrepot::augmenterEntrepot(){
    entrepot_++;
    emit envoyerEntrepot(entrepot_);
}
void compteurEntrepot::decrementerEntrepot(){
    if(entrepot_==0){
        qInfo() << "La quantité d'un produit ne peut être négative.";
        entrepot_==0;
    }
    else{
    entrepot_--;
    }
    emit envoyerEntrepot(entrepot_);
}
