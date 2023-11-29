#ifndef ACCUEIL_H
#define ACCUEIL_H
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class accueil; }
QT_END_NAMESPACE
class accueil : public QMainWindow
{
    Q_OBJECT
public:
    accueil(QWidget *parent = nullptr);
    ~accueil();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private:
    Ui::accueil *ui;
};
#endif // ACCUEIL_H
