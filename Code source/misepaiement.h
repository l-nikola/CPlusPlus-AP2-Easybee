#ifndef MISEPAIEMENT_H
#define MISEPAIEMENT_H
#include <QSqlDatabase>
#include <QDialog>
#include <QSqlTableModel>
namespace Ui {
class misepaiement;
}

class misepaiement : public QDialog
{
    Q_OBJECT

public:
    explicit misepaiement(QWidget *parent = nullptr);
    ~misepaiement();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::misepaiement *ui;
    QSqlDatabase database;
    QSqlTableModel *modeleTable;
};

#endif // MISEPAIEMENT_H
