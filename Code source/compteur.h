#ifndef COMPTEUR_H
#define COMPTEUR_H
#include <QObject>

class compteur: public QObject
{
       Q_OBJECT
public:
    compteur();
    int getMag();
    int getRes();
    void augmenterMag();
    void augmenterRes();
    void decrementerMag();
    void decrementerRes();
signals:
    int envoyerMag(int);
    int envoyerRes(int);
private:
    int mag_;
    int res_;
};
#endif // COMPTEUR_H
