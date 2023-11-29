#ifndef GERANTHUB_H
#define GERANTHUB_H
#include <QDialog>
#include<QSqlDatabase>
#include <QSqlTableModel>
namespace Ui {
class geranthub;
}
class geranthub : public QDialog
{
    Q_OBJECT
public:
    explicit geranthub(QWidget *parent = nullptr);
    ~geranthub();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private:
    Ui::geranthub *ui;
    QSqlDatabase database;
    QSqlTableModel *modeleTable;
};
#endif // GERANTHUB_H
