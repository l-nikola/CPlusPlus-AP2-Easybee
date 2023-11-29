#ifndef COMPTEURENTREPOT_H
#define COMPTEURENTREPOT_H
#include <QObject>
class compteurEntrepot: public QObject
{
       Q_OBJECT
public:
    compteurEntrepot();
    int getEntrepot();
    void augmenterEntrepot();
    void decrementerEntrepot();
signals:
    int envoyerEntrepot(int);
private:
    int entrepot_;
};
#endif // COMPTEUR_H
