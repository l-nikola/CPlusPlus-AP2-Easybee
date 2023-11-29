#include "accueil.h"
#include "./ui_accueil.h"
#include <QPixmap>
#include "authentification.h"
accueil::accueil(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::accueil)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Page d'accueil");
}
accueil::~accueil()
{
    delete ui;
}
void accueil::on_pushButton_clicked()
{
    authentification mainpage;
    mainpage.setModal(true);
    this->hide();
    mainpage.exec();
}
void accueil::on_pushButton_2_clicked()
{
    this->close();
}
