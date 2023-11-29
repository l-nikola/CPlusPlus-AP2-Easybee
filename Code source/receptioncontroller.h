#ifndef RECEPTIONCONTROLLER_H
#define RECEPTIONCONTROLLER_H

#include <QDialog>

namespace Ui {
class receptionController;
}

class receptionController : public QDialog
{
    Q_OBJECT

public:
    explicit receptionController(QWidget *parent = nullptr);
    ~receptionController();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::receptionController *ui;
};

#endif // RECEPTIONCONTROLLER_H
