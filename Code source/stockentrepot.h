#ifndef STOCKENTREPOT_H
#define STOCKENTREPOT_H
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDialog>
#include "compteurentrepot.h"
namespace Ui {
class stockEntrepot;
}

class stockEntrepot : public QDialog
{
    Q_OBJECT

public:
    explicit stockEntrepot(QWidget *parent = nullptr);
    ~stockEntrepot();
    void setup();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
private:
    Ui::stockEntrepot *ui;
    QSqlDatabase database;
    QSqlTableModel *modeleTable;
    compteurEntrepot entrepot_;
};

#endif // STOCKENTREPOT_H
