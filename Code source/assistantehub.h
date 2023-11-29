#ifndef ASSISTANTEHUB_H
#define ASSISTANTEHUB_H
#include <QDialog>
namespace Ui {
class assistantehub;
}
class assistantehub : public QDialog
{
    Q_OBJECT
public:
    explicit assistantehub(QWidget *parent = nullptr);
    ~assistantehub();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
private:
    Ui::assistantehub *ui;
};
#endif // ASSISTANTEHUB_H
