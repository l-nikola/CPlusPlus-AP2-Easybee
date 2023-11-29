#include "adduser.h"
#include "ui_adduser.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
adduser::adduser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adduser)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Inscription d'un client");
}

adduser::~adduser()
{
    delete ui;
}

void adduser::on_pushButton_clicked()
{
   // Récupérer les valeurs saisies dans les champs
   QString nom = ui->lineEdit->text();
   QString prenom = ui->lineEdit_2->text();
   QString identifiant = ui->lineEdit_3->text();
   QString motdepasse = ui->lineEdit_4->text();
   // Vérifier que tous les champs sont remplis
   if (nom.isEmpty() || prenom.isEmpty() || identifiant.isEmpty() || motdepasse.isEmpty()) {
       QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
       return;
   }
   QSqlQuery qry(QSqlDatabase::database("easybeeBDD"));
   qry.prepare("INSERT INTO utilisateur (nom, prenom, identifiant, motdepasse, typeutilisateur) "
                      "VALUES (:nom, :prenom, :identifiant, :motdepasse, '6')");
   qry.bindValue(":nom", nom);
   qry.bindValue(":prenom", prenom);
   qry.bindValue(":identifiant", identifiant);
   qry.bindValue(":motdepasse", motdepasse);
   if (qry.exec()) {
       QMessageBox::information(this, "Confirmation", "L'utilisateur a été ajouté avec succès !");
   }
   else{
       QMessageBox::critical(this, "Erreur", "Impossible d'ajouter l'utilisateur : " + qry.lastError().text());
   }
}
