#ifndef RECEPTIONHUB_H
#define RECEPTIONHUB_H
#include <QDialog>
#include <QSqlTableModel>
#include <QSqlDatabase>
namespace Ui {
class receptionhub;
}
class receptionhub : public QDialog
{
    Q_OBJECT
public:
    explicit receptionhub(QWidget *parent = nullptr);
    ~receptionhub();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::receptionhub *ui;
    QSqlDatabase database;
    QSqlTableModel *modeleTable;
    bool tableVisualised = false;
};
#endif // RECEPTIONHUB_H
