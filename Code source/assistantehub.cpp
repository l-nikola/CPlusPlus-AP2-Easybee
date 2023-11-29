#include "assistantehub.h"
#include "ui_assistantehub.h"
#include <QPixmap>
#include <QMessageBox>
#include "accueil.h"
#include "stockentrepot.h"
#include "saisiecommande.h"
#include "misepaiement.h"
assistantehub::assistantehub(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::assistantehub)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Page de l'assistante de direction");
}
assistantehub::~assistantehub()
{
    delete ui;
}
void assistantehub::on_pushButton_clicked()
{
    stockEntrepot mainpage;
    mainpage.setModal(true);
    this->hide();
    mainpage.exec();
}
void assistantehub::on_pushButton_2_clicked()
{
    saisiecommande mainpage;
    mainpage.setModal(true);
    this->hide();
    mainpage.exec();
}
void assistantehub::on_pushButton_3_clicked()
{
    misepaiement mainpage;
    mainpage.setModal(true);
    this->hide();
    mainpage.exec();
}
void assistantehub::on_pushButton_4_clicked()
{
    QMessageBox::information(this,"Utilisateur déconnecté","Retour à l'accueil d'authentification");
    this->close();
    accueil *authPage = new accueil;
    authPage->show();
}
