#ifndef UKLADROWNAN_H
#define UKLADROWNAN_H

#include<cstring>
#include<iostream>

class UkladRownan
{
private:
    int n;
    long double **A;
    long double **L;
    long double **U;
    long double *x;
    long double *y;
    long double *z;
    long double *yObliczone;
    long double maksimum;
    bool rozwiazane = false;

    long double liczbaLosowa(long double maksimum);
    long long symbolNewtona(int n, int k);


public:
    UkladRownan(int n, long double maksimum);
    virtual ~UkladRownan();
    void losujRownanie();
    void losujRownanieHilbert();
    void losujRownanieBD();

    void pokaz1D(int n, long double x[], std::string napis);
    void pokaz2D(int n, long double *A[], std::string napis);
    void generujLU();
    void dolnoTrojkatna();
    void gornoTrojkatna();
    void rozwiaz();
    int getN();
    long double* getX();
    long double** getA();
    long double* getY();
    long double* getYObliczone();
    long double getSredniBlad();
    long double getMaksBlad();
    long double getMinBlad();
    void setMaksimum(long double maksimum); // tylko ustawia maksimum

};

#endif // UKLADROWNAN_H
