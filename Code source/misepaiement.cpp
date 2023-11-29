#include "misepaiement.h"
#include "ui_misepaiement.h"
#include "accueil.h"
#include <QPixmap>
#include <QMessageBox>
#include <QSqlQuery>
#include "assistantehub.h"
misepaiement::misepaiement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::misepaiement)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Mise en paiement des commandes");
    modeleTable = new QSqlTableModel();
    modeleTable->setTable("commande");
    modeleTable->setFilter("etatCommande = '2' AND idUtilisateur = '2' ");
    modeleTable->select();
    ui->tableView->setModel(modeleTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
}
misepaiement::~misepaiement()
{
    delete ui;
}
void misepaiement::on_pushButton_clicked()
{
    // Récupération du modèle de sélection de la tableView
    QItemSelectionModel *selections = ui->tableView->selectionModel();
    if (selections->selectedIndexes().isEmpty()) {
        QMessageBox::information(this,"Problème de sélection","Aucune ligne n'a été saisie");
    }
    else{
        // Parcours de toutes les lignes sélectionnées
        foreach (const QModelIndex &index, selections->selectedIndexes()) {
            // Récupération de l'ID de la commande à partir de l'index courant
            int idCommande = index.sibling(index.row(), 0).data().toInt();
            // Mise à jour de l'état de la commande
            QSqlQuery query;
            query.prepare("UPDATE commande SET etatCommande = 4 WHERE idCommande = :idCommande");
            query.bindValue(":idCommande", idCommande);
            query.exec();
        }
        QMessageBox::information(this,"Mise en paiement effectuée","Toutes les commandes sélectionnées ont été mis en paiement.");
        //Mis à jour de la tableView
        modeleTable->setTable("commande");
        modeleTable->setFilter("etatCommande = '2' ");
        modeleTable->select();
        ui->tableView->setModel(modeleTable);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    }
    return;
}
void misepaiement::on_pushButton_2_clicked()
{
    assistantehub mainpage;
    mainpage.setModal(true);
    this->hide();
    mainpage.exec();
}
void misepaiement::on_pushButton_3_clicked()
{
    QMessageBox::information(this,"Utilisateur déconnecté","Retour à l'accueil d'authentification");
    this->close();
    accueil *authPage = new accueil;
    authPage->show();
}
