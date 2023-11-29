#include "geranthub.h"
#include "ui_geranthub.h"
#include <QtSql>
#include <QtWidgets>
#include <QSqlTableModel>
#include <QTableView>
#include <QItemSelectionModel>
#include <QAbstractItemModel>
#include <QPixmap>
#include "accueil.h"
geranthub::geranthub(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::geranthub)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Page pour clôturer les commandes");
    QSqlQuery qry(QSqlDatabase::database("easybeeBDD"));
    modeleTable = new QSqlTableModel();
    modeleTable->setTable("commande");
    modeleTable->setFilter("etatCommande = '4' AND idUtilisateur = '2' ");
    modeleTable->select();
    ui->tableView->setModel(modeleTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
}
geranthub::~geranthub()
{
    delete ui;
}
void geranthub::on_pushButton_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Aucun produit sélectionné", "Veuillez sélectionner au moins un produit.");
        return;
    }
    QSqlQuery query;
    QString updateQuery = "UPDATE commande SET etatCommande='5' WHERE idCommande IN (";
    for (int i = 0; i < selectedRows.count(); i++) {
        QModelIndex index = selectedRows.at(i);
        QVariant idValue = modeleTable->data(modeleTable->index(index.row(), 0));
        updateQuery += idValue.toString();
        if (i < selectedRows.count() - 1) {
            updateQuery += ",";
        }
    }
    updateQuery += ")";
    if (!query.exec(updateQuery)) {
        QMessageBox::warning(this, "Erreur", "La mise à jour de l'état des commandes a échoué :\n\n" + query.lastError().text());
        return;
    }
    else{
        QMessageBox::information(this,"Paiement effectué","Les commandes sélectionnées ont été clôturées.");
    }
    modeleTable->select();
}
void geranthub::on_pushButton_2_clicked()
{
    QMessageBox::information(this,"Utilisateur déconnecté","Retour à l'accueil d'authentification");
    this->close();
    accueil *authPage = new accueil;
    authPage->show();
}
