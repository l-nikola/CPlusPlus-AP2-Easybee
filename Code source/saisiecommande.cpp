#include "saisiecommande.h"
#include "ui_saisiecommande.h"
#include "accueil.h"
#include "assistantehub.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QModelIndex>
#include <QSqlRecord>
saisiecommande::saisiecommande(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saisiecommande)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Saisie des commandes");
    modeleTable = new QSqlTableModel();
    modeleTable->setTable("detailCommande");
    modeleTable->setFilter("id_utilisateur = '2' AND quantiteNecessaire != 0 AND quantitePlacee != 0");
    modeleTable->select();
    ui->tableView->setModel(modeleTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}
saisiecommande::~saisiecommande()
{
    delete ui;
}
void saisiecommande::on_pushButton_clicked()
{
    //suite code à finir
    QSqlQuery qry(QSqlDatabase::database("easybeeBDD"));
    QModelIndex index = ui->tableView->currentIndex();
    QSqlRecord record = modeleTable->record(index.row());
    int id_commande = modeleTable->record(index.row()).value("id_commande").toInt();
    if(!index.isValid()){
        QMessageBox::warning(this,"Erreur de sélection","Sélectionnez une ligne");
        return;
    }
    qry.prepare("SELECT quantiteNecessaire, quantitePlacee, id_produit FROM detailCommande WHERE id_commande = :id_commande");
    qry.bindValue(":id_commande", id_commande);
    qry.exec();
    int quantiteNecessaire = record.value("quantiteNecessaire").toInt();
    int quantitePlacee = record.value("quantitePlacee").toInt();
    int id_produit = record.value("id_produit").toInt();
    qry.prepare("SELECT stockEntrepot FROM produit WHERE id = :id_produit");
    qry.bindValue(":id_produit",id_produit);
    qry.exec();
    int stockEntrepot = record.value("stockEntrepot").toInt();
    stockEntrepot = stockEntrepot + quantitePlacee;
    quantiteNecessaire = quantiteNecessaire - quantitePlacee;
    quantitePlacee = 0;
    qry.prepare("UPDATE detailCommande set quantiteNecessaire = :quantiteNecessaire, quantitePlacee = :quantitePlacee WHERE id_commande = :id_commande");
    qry.bindValue(":quantiteNecessaire",quantiteNecessaire);
    qry.bindValue(":quantitePlacee",quantitePlacee);
    qry.bindValue(":id_commande",id_commande);
    qry.exec();
    qry.prepare("UPDATE produit set stockEntrepot = :stockEntrepot WHERE id_produit = :id_produit");
    qry.bindValue("stockEntrepot",stockEntrepot);
    qry.bindValue("id_produit",id_produit);
    qry.exec();
    QMessageBox::information(this,"Saisie effectuée","Les produits placés par le fournisseur ont été placé dans l'entrepôt.");
    if(quantiteNecessaire == 0){
        //réception totale
        qry.prepare("UPDATE commande SET etatCommande='2' WHERE idCommande = :id_commande");
        qry.bindValue(":id_commande",id_commande);
        qry.exec();
        QMessageBox::information(this,"Réception totale","La commande a reçu tous les produits commandés.");
    }
    else{
        //réception partielle
        qry.prepare("UPDATE commande SET etatCommande='3' WHERE idCommande = :id_commande");
        qry.bindValue(":id_commande",id_commande);
        qry.exec();
    }
    modeleTable = new QSqlTableModel();
    modeleTable->setTable("detailCommande");
    modeleTable->setFilter("id_utilisateur = '2' AND quantiteNecessaire != 0 AND quantitePlacee != 0");
    modeleTable->select();
    ui->tableView->setModel(modeleTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    return;
}
void saisiecommande::on_pushButton_2_clicked()
{
    assistantehub mainpage;
    mainpage.setModal(true);
    this->hide();
    mainpage.exec();
}
void saisiecommande::on_pushButton_3_clicked()
{
    QMessageBox::information(this,"Utilisateur déconnecté","Retour à l'accueil d'authentification");
    this->close();
    accueil *authPage = new accueil;
    authPage->show();
}
