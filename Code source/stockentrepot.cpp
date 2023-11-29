#include "stockentrepot.h"
#include "ui_stockentrepot.h"
#include <QPixmap>
#include <QMessageBox>
#include "accueil.h"
#include "assistantehub.h"
#include "compteurentrepot.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>
#include <QMessageBox>
stockEntrepot::stockEntrepot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stockEntrepot)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Ravitaillement de l'entrepôt");
    modeleTable = new QSqlTableModel();
    modeleTable->setTable("produit");
    modeleTable->setFilter("stockMinEntrepot > stockEntrepot");
    modeleTable->select();
    ui->tableView->setModel(modeleTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->label_2->setNum(entrepot_.getEntrepot());
}
stockEntrepot::~stockEntrepot()
{
    delete ui;
}
void stockEntrepot::setup() {
    // Mettre à jour les labels avec les valeurs initiales de mag_ et res_
    ui->label_2->setNum(entrepot_.getEntrepot());
    // Connecter les signaux et slots entre les boutons et les méthodes correspondantes
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(decrementerEntrepot()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(augmenterEntrepot()));
    // Connecter les signaux et slots entre les objets mag_ et res_ et les labels correspondants
    connect(&entrepot_, SIGNAL(envoyerEntrepot(int)), ui->label_2, SLOT(setNum(int)));
}
void stockEntrepot::on_pushButton_clicked() //decrementer entrepot
{
    entrepot_.decrementerEntrepot();
    ui->label_2->setNum(entrepot_.getEntrepot());
}
void stockEntrepot::on_pushButton_2_clicked() //augmenter entrepot
{
    entrepot_.augmenterEntrepot();
    ui->label_2->setNum(entrepot_.getEntrepot());
}
void stockEntrepot::on_pushButton_3_clicked()
{
    //Initialisation bdd et sélection du produit
    QSqlQuery qry(QSqlDatabase::database("easybeeBDD"));
    QModelIndex index = ui->tableView->currentIndex();
    int id = modeleTable->record(index.row()).value("id").toInt();
    if(!index.isValid()){
        QMessageBox::warning(this,"Erreur de sélection","Sélectionnez une ligne");
        return;
    }
    //Récupération des données
    QSqlRecord record = modeleTable->record(index.row());
    qry.prepare("INSERT INTO commande (etatCommande, idUtilisateur, dateCommande, prixTotal) "
                  "VALUES (1, 2, :dateCommande, 0)");
    qry.bindValue(":dateCommande", QDate::currentDate());
    qry.exec();
    int id_commande = qry.lastInsertId().toInt();
    qry.prepare("SELECT prixUnitaire, tauxTVA FROM produit WHERE id = :id");
    qry.bindValue(":id", id);
    qry.exec();
    double prixUnitaire = record.value("prixUnitaire").toDouble();
    double tauxTVA = record.value("tauxTVA").toDouble();
    qry.prepare("INSERT INTO detailCommande (id_commande, id_produit, quantitePlacee, quantiteNecessaire, prixLigne, id_utilisateur) "
                  "VALUES (:id_commande, :id_produit, 0, :quantiteNecessaire, :prixLigne, 2)");
    qry.bindValue(":id_commande",id_commande);
    qry.bindValue(":id_produit", id);
    qry.bindValue(":quantiteNecessaire", ui->label_2->text().toInt());
    qry.bindValue(":prixLigne", prixUnitaire * ui->label_2->text().toInt());
    qry.exec();
    double prixLigne = prixUnitaire + prixUnitaire*tauxTVA * ui->label_2->text().toInt();
    qry.prepare("UPDATE commande SET prixTotal = :prixLigne WHERE idCommande = :id_commande");
    qry.bindValue(":prixLigne", prixLigne);
    qry.bindValue(":id_commande", id_commande);
    qry.exec();
    QMessageBox::information(this,"Produit commandé","La commande a été transmis au fournisseur correspondant");
}
void stockEntrepot::on_pushButton_4_clicked()
{
    assistantehub mainpage;
    mainpage.setModal(true);
    this->hide();
    mainpage.exec();
}
void stockEntrepot::on_pushButton_5_clicked()
{
    QMessageBox::information(this,"Utilisateur déconnecté","Retour à l'accueil d'authentification");
    this->close();
    accueil *authPage = new accueil;
    authPage->show();
}
