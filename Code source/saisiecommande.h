#ifndef SAISIECOMMANDE_H
#define SAISIECOMMANDE_H
#include <QSqlDatabase>
#include <QDialog>
#include <QSqlTableModel>
namespace Ui {
class saisiecommande;
}

class saisiecommande : public QDialog
{
    Q_OBJECT

public:
    explicit saisiecommande(QWidget *parent = nullptr);
    ~saisiecommande();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
private:
    Ui::saisiecommande *ui;
    QSqlDatabase database;
    QSqlTableModel *modeleTable;
};

#endif // SAISIECOMMANDE_H
