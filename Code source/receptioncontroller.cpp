#include "receptioncontroller.h"
#include "ui_receptioncontroller.h"
#include <QPixmap>
#include "accueil.h"
#include <QMessageBox>
#include "receptionhub.h"
#include "receptioncommande.h"
receptionController::receptionController(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::receptionController)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Page du réceptionniste de la commande");
}
receptionController::~receptionController()
{
    delete ui;
}
void receptionController::on_pushButton_clicked()
{
    receptioncommande mainpage;
    mainpage.setModal(true);
    this->hide();
    mainpage.exec();
}
void receptionController::on_pushButton_2_clicked()
{
    receptionhub mainpage;
    mainpage.setModal(true);
    this->hide();
    mainpage.exec();
}
void receptionController::on_pushButton_3_clicked()
{
    QMessageBox::information(this,"Utilisateur déconnecté","Retour à l'accueil d'authentification");
    this->close();
    accueil *authPage = new accueil;
    authPage->show();
}
