#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H
#include <QSqlError>
#include <QDialog>
namespace Ui {
class authentification;
}
class authentification : public QDialog
{
    Q_OBJECT
public:
    explicit authentification(QWidget *parent = nullptr);
    ~authentification();
private slots:
    void on_pushButton_clicked();
private:
    Ui::authentification *ui;
    void showError(const QSqlError &authentificate);
};
#endif // AUTHENTIFICATION_H
