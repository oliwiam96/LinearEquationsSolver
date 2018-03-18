#ifndef MACIERZ_H
#define MACIERZ_H

#include <QWidget>
#include "UkladRownan.h"
#include "UkladRownanPrzedzial.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QGridLayout;
QT_END_NAMESPACE

#include<cstdlib>


class Macierz : public QWidget
{
    Q_OBJECT
public:
    explicit Macierz(QWidget *parent = 0);
    virtual ~Macierz();
    std::vector <QLineEdit*> getAInput();
    void setAInput(std::vector <QLineEdit*> AInput);
    void nowyUkladRownan(int n, long double maksimum);
    void losuj();
    void losujHilbert();
    void losujBD();
    UkladRownan* ukladRownan = NULL;
    UkladRownanPrzedzial* ukladRownanPrzedzial = NULL;
    void przepiszOdwrocone();
    void przepiszOdwroconePrzedzial();
    void rozwiazPrzedzial();

private:

    QGridLayout *mainLayout;
    std::vector <QLineEdit*> AInput;
    void utworz(int n, long double maksimum);
    void usun();
    void przepisz();
    int MAX_WYMIAR_WYSWIETL = 15;

signals:

public slots:
};

#endif // MACIERZ_H
