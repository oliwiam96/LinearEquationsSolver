#include <QtWidgets>
#include <QSpacerItem>

#include <cmath>
#include<cstring>

#include "Macierz.h"
#include "konwersja.h"
#include "rounding.h"


Macierz::Macierz(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout;
    setLayout(mainLayout);
    utworz(5, 10.0);
}
Macierz::~Macierz()
{
    int n = ukladRownan->getN();
    if(n <= MAX_WYMIAR_WYSWIETL)
    {
        for(int i = 0; i <  n*(n+1); i++)
        {
            delete AInput[i];
        }
        AInput.clear();
    }
    delete ukladRownan;
    if(ukladRownanPrzedzial)
    {
        delete ukladRownanPrzedzial;
    }
}

void Macierz::setAInput(std::vector <QLineEdit*> A)
{
    this->AInput = A;
}
std::vector <QLineEdit*> Macierz::getAInput()
{
    return this->AInput;
}
void Macierz::utworz(int n, long double maksimum)
{
    ukladRownan = new UkladRownan(n, maksimum); 

    long double **A = ukladRownan->getA();
    long double *y = ukladRownan->getY();

    if(n <= MAX_WYMIAR_WYSWIETL)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                QLineEdit *linia_A = new QLineEdit(toString(A[i][j]));
                linia_A->setCursorPosition(0);
                AInput.push_back(linia_A);
                mainLayout->addWidget(AInput[i*(n+1) + j], i+1, j);
            }
            QLineEdit* y_pole = new QLineEdit(toString(y[i]));
            y_pole->setStyleSheet("QLineEdit { background: rgb(0, 255, 255); selection-background-color: rgb(233, 99, 0); }");
            y_pole->setCursorPosition(0);
            AInput.push_back(y_pole);
            mainLayout->addWidget(AInput[i*(n+1) + n], i+1, n);
        }
     }
    else
    {
        std::cout<<"Duzy wymiar macierzy. Brak możliwosci edycji!"<<std::endl;
        QMessageBox msgBoxN;
        msgBoxN.setText("Duży wymiar macierzy! Brak możliwości edycji. Przyciski losowania działają standardowo");
        msgBoxN.exec();
    }

}
void Macierz::usun()
{
    // usuwanie starych obiektow
    int stare_n = ukladRownan->getN();
    if(stare_n <= MAX_WYMIAR_WYSWIETL)
    {
        for(int i = 0; i < stare_n*(stare_n+1); i++)
        {
            mainLayout->removeWidget(AInput[i]);
            delete AInput[i];
        }
        AInput.clear();
    }
    delete ukladRownan;
    if(ukladRownanPrzedzial)
    {
        delete ukladRownanPrzedzial;
    }
}

void Macierz::nowyUkladRownan(int n, long double maksimum)
{
    usun();
    utworz(n, maksimum);
}

void Macierz::losuj()
{
    ukladRownan->losujRownanie();
    this->przepisz();

}
void Macierz::losujHilbert()
{
    ukladRownan->losujRownanieHilbert();
    this->przepisz();
}
void Macierz::losujBD()
{
    ukladRownan->losujRownanieBD();
    this->przepisz();
}
void Macierz::przepisz()
{
    if(ukladRownan->getN() <= MAX_WYMIAR_WYSWIETL)
    {
        long double **A = ukladRownan->getA();
        long double *y = ukladRownan->getY();
        int n = ukladRownan->getN();
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                AInput[i*(n+1) + j]->setText(toString(A[i][j]));
                AInput[i*(n+1) + j]->setCursorPosition(0);
            }
            AInput[i*(n+1) + n]->setText(toString(y[i]));
            AInput[i*(n+1) + n]->setCursorPosition(0);
        }
     }
}
void Macierz::przepiszOdwrocone()
{
    if(ukladRownan->getN() <= MAX_WYMIAR_WYSWIETL)
    {
        long double **A = ukladRownan->getA();
        long double *y = ukladRownan->getY();
        int n = ukladRownan->getN();
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                A[i][j] = toLDouble(AInput[i*(n+1) + j]->text());
            }
            y[i] = toLDouble(AInput[i*(n+1) + n]->text());
        }
    }
}
void Macierz::rozwiazPrzedzial()
{
    int n = ukladRownan->getN();
    this->ukladRownanPrzedzial = new UkladRownanPrzedzial(n);
    this->przepiszOdwroconePrzedzial();
    ukladRownanPrzedzial->rozwiaz();
}
void Macierz::przepiszOdwroconePrzedzial()
{
    I **A = ukladRownanPrzedzial->getA();
    I *y = ukladRownanPrzedzial->getY();
    long double **APoz = ukladRownan->getA();
    long double *yPoz = ukladRownan->getY();
    int n = ukladRownan->getN();

    if(n > MAX_WYMIAR_WYSWIETL)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                A[i][j].set(APoz[i][j], APoz[i][j]);
            }
            y[i].set(yPoz[i], yPoz[i]);
        }
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                A[i][j].set(returnLow(AInput[i*(n+1) + j]->text().toStdString()),
                        returnUp(AInput[i*(n+1) + j]->text().toStdString()));
            }
            y[i].set(returnLow(AInput[i*(n+1) + n]->text().toStdString()),
                    returnUp(AInput[i*(n+1) + n]->text().toStdString()));
        }
    }
}

