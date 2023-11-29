#include "receptioncommande.h"
#include "ui_receptioncommande.h"
#include "accueil.h"
#include "receptioncontroller.h"
#include <QMessageBox>
#include <QPixmap>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlRecord>
receptioncommande::receptioncommande(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::receptioncommande)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Ravitaillement de produits");
    modeleTable = new QSqlTableModel();
    modeleTable->setTable("produit");
    modeleTable->setFilter("stockMinMag > stockMag OR stockMinRes > stockRes");
    modeleTable->select();
    ui->tableView->setModel(modeleTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->label_2->setNum(0);
    ui->label_3->setNum(0);
}
receptioncommande::~receptioncommande()
{
    delete ui;
}
void receptioncommande::on_pushButton_6_clicked()
{
    receptionController mainpage;
    mainpage.setModal(true);
    this->hide();
    mainpage.exec();
}
void receptioncommande::on_pushButton_7_clicked()
{
    QMessageBox::information(this,"Utilisateur déconnecté","Retour à l'accueil d'authentification");
    this->close();
    accueil *authPage = new accueil;
    authPage->show();
}
void receptioncommande::setup() {
    // Mettre à jour les labels avec les valeurs initiales de mag_ et res_
    ui->label_2->setNum(comptmag_.getMag());
    ui->label_3->setNum(comptres_.getRes());
    // Connecter les signaux et slots entre les boutons et les méthodes correspondantes
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(decrementerMag()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(augmenterMag()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(decrementerRes()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(augmenterRes()));
    // Connecter les signaux et slots entre les objets mag_ et res_ et les labels correspondants
    connect(&comptmag_, SIGNAL(envoyerMag(int)), ui->label_2, SLOT(setNum(int)));
    connect(&comptres_, SIGNAL(envoyerRes(int)), ui->label_3, SLOT(setNum(int)));
}
void receptioncommande::on_pushButton_clicked() //stockmag --
{
    comptmag_.decrementerMag();
    ui->label_2->setNum(comptmag_.getMag());
}
void receptioncommande::on_pushButton_3_clicked() //stockmag ++
{
    comptmag_.augmenterMag();
    ui->label_2->setNum(comptmag_.getMag());
}
void receptioncommande::on_pushButton_2_clicked() //stockres --
{
    comptres_.decrementerRes();
    ui->label_3->setNum(comptres_.getRes());
}
void receptioncommande::on_pushButton_4_clicked() //stockres ++
{
    comptres_.augmenterRes();
    ui->label_3->setNum(comptres_.getRes());
}
void receptioncommande::on_pushButton_5_clicked()
{
    //Initialisation bdd et sélection du produit
    QSqlQuery qry(QSqlDatabase::database("easybeeBDD"));
    QModelIndex index = ui->tableView->currentIndex();
    int id = modeleTable->record(index.row()).value("id").toInt();
    if(!index.isValid()){
        QMessageBox::warning(this,"Aucune opération effectuée","Sélectionnez une ligne");
        return;
    }
    //Récupération des données
    QSqlRecord record = modeleTable->record(index.row());
    qry.prepare("SELECT id, stockMag, stockRes, stockEntrepot FROM PRODUIT WHERE id = :id");
    qry.bindValue(":id",id);
    qry.exec();
    int stockMag = record.value("stockMag").toInt();
    int stockRes = record.value("stockRes").toInt();
    int stockEntrepot = record.value("stockEntrepot").toInt();
    qDebug() << "id: " << id;
    qDebug() << "stockMag : " << stockMag;
    qDebug() << "stockRes : " << stockRes;
    qDebug() << "stockEntrepot : " << stockEntrepot;
    int magValue = ui->label_2->text().toInt();
    int resValue = ui->label_3->text().toInt();
    qDebug() << "magValue : " << magValue;
    qDebug() << "resValue : " << resValue;
    //Gérer les données
    if(magValue == 0 && resValue == 0){
        QMessageBox::warning(this,"Aucune opération effectué","Sélectionnez une quantité de produits à mettre dans le stock magasin et dans la réserve");
    }
    else if(stockEntrepot < magValue + resValue){
        QMessageBox::warning(this,"Aucune opération effectué","Ressources indisponibles dans de telles quantités");
    }
    else{
        stockEntrepot = stockEntrepot - magValue - resValue;
        stockMag = stockMag + magValue;
        stockRes = stockRes + resValue;
        qry.prepare("UPDATE produit SET stockMag = :stockMag, stockRes = :stockRes, stockEntrepot = :stockEntrepot WHERE id = :id");
        qry.bindValue(":stockMag",stockMag);
        qry.bindValue(":stockRes",stockRes);
        qry.bindValue(":stockEntrepot",stockEntrepot);
        qry.bindValue(":id",id);
        if(qry.exec()){
            QMessageBox::information(this,"Opération effectué","Les produits ont été positionnés");
        }
        else{
            qry.lastError();
        }
        //Réinitialisation de la page
        ui->label_2->setNum(0);
        ui->label_3->setNum(0);
        modeleTable->setTable("produit");
        modeleTable->setFilter("stockMinMag > stockMag OR stockMinRes > stockRes");
        modeleTable->select();
        ui->tableView->setModel(modeleTable);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        qDebug() << "stockMag : " << stockMag;
        qDebug() << "stockRes : " << stockRes;
        qDebug() << "stockEntrepot : " << stockEntrepot;
    }
    return;
}
