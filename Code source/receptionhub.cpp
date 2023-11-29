#include "receptionhub.h"
#include "ui_receptionhub.h"
#include <QtSql>
#include <QtWidgets>
#include <QSqlTableModel>
#include <QTableView>
#include <QItemSelectionModel>
#include <QAbstractItemModel>
#include <QPixmap>
#include <QMessageBox>
#include "accueil.h"
#include "receptioncontroller.h"
receptionhub::receptionhub(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::receptionhub)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Gestion des commandes des clients");
    QSqlQuery qry(QSqlDatabase::database("easybeeBDD"));
    modeleTable = new QSqlTableModel();
    modeleTable->setTable("commande");
    modeleTable->setFilter("etatCommande IN ('1', '3') AND idUtilisateur = '6' ");
    modeleTable->select();
    ui->tableView->setModel(modeleTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableVisualised = false;
}
receptionhub::~receptionhub()
{
    delete ui;
}
void receptionhub::on_pushButton_clicked()
{
    // Efface la sélection actuelle
    ui->tableView->clearSelection();
    // Rafraîchit la table commande
    modeleTable->setFilter("etatCommande IN ('1', '3') AND idUtilisateur = '6' ");
    modeleTable->select();
    // Réinitialise la vue
    ui->tableView->setModel(modeleTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableVisualised = false;
}
void receptionhub::on_pushButton_2_clicked()
{
    QMessageBox::information(this,"Utilisateur déconnecté","Retour à l'accueil d'authentification");
    this->close();
    accueil *authPage = new accueil;
    authPage->show();
}
void receptionhub::on_tableView_doubleClicked(const QModelIndex &index)
{
    // Récupérer l'id de la commande sélectionnée
    int idCommande = modeleTable->record(index.row()).value("idCommande").toInt();
    // Créer un modèle pour la table detailCommande
    QSqlTableModel *modeleDetailCommande = new QSqlTableModel();
    modeleDetailCommande->setTable("detailCommande");
    // Appliquer un filtre pour n'afficher que les détails de la commande sélectionnée
    QString filtre = QString("id_commande = %1").arg(idCommande);
    modeleDetailCommande->setFilter(filtre);
    modeleDetailCommande->select();
    // Mettre à jour la vue de table avec le nouveau modèle filtré
    ui->tableView->setModel(modeleDetailCommande);
    tableVisualised = true;
}
void receptionhub::on_pushButton_3_clicked()
{
    // Etape 1 : vérification
    // Vérifie que la tableView actuelle visualise la table detailCommande
    if(!tableVisualised)
    {
        QMessageBox::warning(this, "Sélection requise", "Veuillez sélectionner une commande d'un client.");
        return;
    }
    // Vérifie qu'une ligne a été sélectionnée dans detailCommande
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (selectedRows.empty()) {
        QMessageBox::warning(this, "Sélection requise", "Veuillez sélectionner une ligne produit à remplir.");
        return;
    }
    QModelIndex index = selectedRows.first();

    // Etape 2 : récupération des données
    // Récupérer l'indice de la ligne sélectionnée
    int selectedRow = ui->tableView->currentIndex().row();
    // Obtenir l'index de chaque colonne
    QModelIndex index_id_commande = ui->tableView->model()->index(selectedRow, 0);
    QModelIndex index_id_produit = ui->tableView->model()->index(selectedRow, 1);
    QModelIndex index_quantiteNecessaire = ui->tableView->model()->index(selectedRow, 2);
    QModelIndex index_quantitePlacee = ui->tableView->model()->index(selectedRow, 3);
    // Obtenir les valeurs de chaque cellule dans la ligne sélectionnée
    int id_commande = ui->tableView->model()->data(index_id_commande).toInt();
    int id_produit = ui->tableView->model()->data(index_id_produit).toInt();
    int quantiteNecessaire = ui->tableView->model()->data(index_quantiteNecessaire).toInt();
    int quantitePlacee = ui->tableView->model()->data(index_quantitePlacee).toInt();
    //obtenir les dernières données dans la table produit
    QSqlQuery query(QSqlDatabase::database("easybeeBDD"));
    query.prepare("SELECT stockMag, stockRes FROM produit WHERE id = :id_produit");
    query.bindValue(":id_produit",id_produit);
    query.exec();
    query.next();
    int stockMag = query.value("stockMag").toInt();
    int stockRes = query.value("stockRes").toInt();
    //vérification de la récupération
    qDebug() << "id_commande :" << id_commande;
    qDebug() << "quantiteNecessaire :" << quantiteNecessaire;
    qDebug() << "quantitePlacee :" << quantitePlacee;
    qDebug() << "id_produit :" << id_produit;
    qDebug() << "stockMag :" << stockMag;
    qDebug() << "stockRes :" << stockRes;

    // Etape 3 : gestion des données
    if(quantiteNecessaire == quantitePlacee){
        QMessageBox::information(this,"Produits délivrés","La quantité nécéssaire au client dans cette ligne a déjà été réglé");
    }
    if (stockMag + stockRes >= quantiteNecessaire - quantitePlacee) {
        // Appeler la méthode de gestion 1
        while (quantitePlacee < quantiteNecessaire){
            if(stockMag > 0){
                stockMag -- ;
                query.prepare("UPDATE produit SET stockMag = :stockMag WHERE id = :id_produit");
                query.bindValue(":stockMag",stockMag);
                query.bindValue(":id_produit", id_produit);
                query.exec();
                quantitePlacee ++ ;
            }
            else{
                stockRes -- ;
                query.prepare("UPDATE produit SET stockRes = :stockRes WHERE id = :id_produit");
                query.bindValue(":stockRes",stockRes);
                query.bindValue(":id_produit",id_produit);
                query.exec();
                quantitePlacee ++ ;
            }
            query.prepare("UPDATE detailCommande SET quantitePlacee = :quantitePlacee WHERE id_produit = :id_produit AND id_commande = :id_commande");
            query.bindValue(":quantitePlacee",quantitePlacee);
            query.bindValue(":id_commande",id_commande);
            query.bindValue(":id_produit",id_produit);
            query.exec();
        }
        QMessageBox::information(this, "Produit délivrés","La quantité nécessaire a été réceptionnée pour cette ligne");
        //vérifier les échanges de produits entre le stock et la commande
        qDebug() << "resultat stockMag : " << stockMag;
        qDebug() << "resultat stockRes : " << stockRes;
        qDebug() << "resultat quantitePlacee : " << quantitePlacee;
        qDebug() << "resultat quantiteNecessaire : " << quantiteNecessaire;
    }
    else {
        if (stockMag + stockRes == 0) {
            //Impossible de remplir les produits nécessaires à la commande
            QMessageBox::warning(this, "Insertion du produit impossible", "Le produit est en rupture de stock.");
        }
        else {
            // Appeler la méthode de gestion 2
            while (stockMag + stockRes != 0) {
                //program
                if(stockMag > 0){
                    stockMag -- ;
                    query.prepare("UPDATE produit SET stockMag = :stockMag WHERE id = :id_produit");
                    query.bindValue(":stockMag",stockMag);
                    query.bindValue(":id_produit",id_produit);
                    query.exec();
                    quantitePlacee ++ ;
                }
                else{
                    if(stockRes > 0){
                        stockRes -- ;
                        query.prepare("UPDATE produit SET stockRes = :stockRes WHERE id = :id_produit");
                        query.bindValue(":stockRes",stockRes);
                        query.bindValue(":id_produit",id_produit);
                        query.exec();
                        quantitePlacee ++ ;
                    }
                }
                query.prepare("UPDATE detailCommande SET quantitePlacee = :quantitePlacee WHERE id_produit = :id_produit AND id_commande = :id_commande");
                query.bindValue(":quantitePlacee",quantitePlacee);
                query.bindValue(":id_commande",id_commande);
                query.bindValue(":id_produit",id_produit);
                query.exec();
            }
            QMessageBox::information(this, "Produit délivrés","Il reste quelques produits à placer en raison d'une rupture de stock.");
            //vérifier les échanges de produits entre le stock et la commande
            qDebug() << "resultat stockMag : " << stockMag;
            qDebug() << "resultat stockRes : " << stockRes;
            qDebug() << "resultat quantitePlacee : " << quantitePlacee;
            qDebug() << "resultat quantiteNecessaire : " << quantiteNecessaire;
        }
    }

    // Etape 4 : changement d'état de la commande
    // Vérifier si toutes les lignes de la commande ont leur quantité nécessaire égale à leur quantité placée
    query.prepare("SELECT COUNT(*) FROM detailCommande WHERE id_commande = :id_commande AND quantiteNecessaire != quantitePlacee;");
    query.bindValue(":id_commande", id_commande);
    query.exec();
    query.next();
    int count_incomplete = query.value(0).toInt();
    if (count_incomplete == 0) {
        // Toutes les lignes sont complètes : RT - totale
        query.prepare("UPDATE commande SET etatCommande='2' WHERE idCommande = :id_commande");
        query.bindValue(":id_commande",id_commande);
        query.exec();
        query.next();
        QMessageBox::information(this,"récepetion complète","tous les produits complétés ont été insérées");
    }
    else {
        // Tester si il y a des lignes incomplètes
        query.prepare("SELECT COUNT(*) FROM detailCommande WHERE id_commande = :id_commande AND :quantitePlacee > 0;");
        query.bindValue(":id_commande", id_commande);
        query.bindValue(":quantitePlacee", quantitePlacee);
        query.exec();
        query.next();
        int count_modifie = query.value(0).toInt();
        if (count_modifie > 0) {
            //Il y a eu au moins une ligne remplie de produits : RP - partielle
            query.prepare("UPDATE commande SET etatCommande='3' WHERE idCommande = :id_commande");
            query.bindValue(":id_commande",id_commande);
            query.exec();
            query.next();
        }
    }
    on_pushButton_clicked();
    return;
}
void receptionhub::on_pushButton_4_clicked()
{
    receptionController mainpage;
    mainpage.setModal(true);
    this->hide();
    mainpage.exec();
}
