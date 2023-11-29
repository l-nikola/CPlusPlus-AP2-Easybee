#include "admin.h"
#include "ui_admin.h"
#include <QPixmap>
#include <QMessageBox>
#include "accueil.h"
#include <QSqlQuery>
#include <QSql>
#include <QtWidgets>
#include <QSqlTableModel>
#include <QTableView>
#include <QItemSelectionModel>
#include <QAbstractItemModel>
#include "adduser.h"
admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    QPixmap image(":/images/easybee.png");
    ui->label->setPixmap(image);
    this->setWindowTitle("Page pour clôturer les commandes");
    QSqlQuery qry(QSqlDatabase::database("easybeeBDD"));
    modeleTable = new QSqlTableModel();
    modeleTable->setTable("utilisateur");
    modeleTable->select();
    ui->tableView->setModel(modeleTable);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    modeleTable2 = new QSqlTableModel();
    modeleTable2->setTable("typeutilisateur");
    modeleTable2->select();
    ui->tableView_2->setModel(modeleTable2);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setSelectionMode(QAbstractItemView::MultiSelection);
}
admin::~admin()
{
    delete ui;
}
void admin::on_pushButton_clicked()
{
    QMessageBox::information(this,"Utilisateur déconnecté","Retour à l'accueil d'authentification");
    this->close();
    accueil *authPage = new accueil;
    authPage->show();
}

void admin::on_pushButton_2_clicked()
{
    adduser mainpage;
    mainpage.setModal(true);
    mainpage.exec();
}

