#ifndef RECEPTIONCOMMANDE_H
#define RECEPTIONCOMMANDE_H
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDialog>
#include "compteur.h"
namespace Ui {
class receptioncommande;
}

class receptioncommande : public QDialog
{
    Q_OBJECT

public:
    explicit receptioncommande(QWidget *parent = nullptr);
    ~receptioncommande();
    void setup();
private slots:

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::receptioncommande *ui;
    QSqlDatabase database;
    QSqlTableModel *modeleTable;
    compteur comptmag_;
    compteur comptres_;
};

#endif // RECEPTIONCOMMANDE_H
