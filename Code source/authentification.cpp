#include "authentification.h"
#include "ui_authentification.h"
#include "initdb.h"
#include <QPixmap>
#include <QtSql>
#include <QMessageBox>
#include <QtWidgets>
#include "geranthub.h"
#include "assistantehub.h"
#include "admin.h"
#include "receptioncontroller.h"
authentification::authentification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authentification)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Page d'authentification");
    if(!QSqlDatabase::drivers().contains("QMYSQL"))
        QMessageBox::critical(this,"Impossible de se connecter à la base de données","Il y a peut être un problème de connexion avec le driver QMYSQL");
    QSqlError authentificate = initDB();
    if(authentificate.type() != QSqlError::NoError){
        showError(authentificate);
        return;
    }
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}
authentification::~authentification()
{
    delete ui;
}
void authentification::showError(const QSqlError &authentificate)
{
    QMessageBox::critical(this,"Impossible d'initialiser la connexion base de données","Erreur d'initialisation à la base de données" + authentificate.text());
}
void authentification::on_pushButton_clicked()
{
    QString identifiant=ui->lineEdit->text();
    QString motdepasse=ui->lineEdit_2->text();
    QSqlQuery authentificate;
    authentificate.prepare("SELECT typeUtilisateur FROM utilisateur WHERE identifiant = ? AND motdepasse = ?");
    authentificate.addBindValue(identifiant);
    authentificate.addBindValue(motdepasse);
    authentificate.exec();
    if (authentificate.next()) {
        QString typeUtilisateur = authentificate.value(0).toString();
        if (typeUtilisateur == "1") {
            geranthub mainpage;
            mainpage.setModal(true);
            this->hide();
            mainpage.exec();
        }
        else if (typeUtilisateur == "2") {
            assistantehub mainpage;
            mainpage.setModal(true);
            this->hide();
            mainpage.exec();
        }
        else if (typeUtilisateur == "3") {
            receptionController mainpage;
            mainpage.setModal(true);
            this->hide();
            mainpage.exec();
        }
        else if (typeUtilisateur == "4") {
            admin mainpage;
            mainpage.setModal(true);
            this->hide();
            mainpage.exec();
        }
        else if (typeUtilisateur == "5") {
            QMessageBox::information(this,"Accès refusé", "Votre accès vous a été retiré.");
        }
    }
    else {
        QMessageBox::information(this,"Accès refusé", "Identifiant ou mot de passe incorrect.");
    }
}
