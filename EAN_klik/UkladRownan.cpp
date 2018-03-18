#include "UkladRownan.h"
#include<cstring>
#include<cmath>
#include<iostream>
#include<boost/numeric/interval.hpp>

using namespace std;

int sign_polynomial(long double x, long double P[], int sz) {
  using namespace boost::numeric;
  using namespace interval_lib;
  typedef interval<long double> I_aux;

  I_aux::traits_type::rounding rnd;
  typedef unprotect<I_aux>::type I;

  I y = P[sz - 1];
  for(int i = sz - 2; i >= 0; i--)
    y = y * x + P[i];

  using namespace compare::certain;
  if (y > 0.) return 1;
  if (y < 0.) return -1;
  return 0;
}

UkladRownan::UkladRownan(int n, long double maksimum)
{
    this->n = n;
    this->maksimum = maksimum;
    // tworzenie nowych obiektow
    A = new long double*[n];
    y = new long double [n];
    for(int i = 0; i < n; i++)
    {
        A[i] = new long double[n];
    }
    losujRownanie();
}
UkladRownan::~UkladRownan()
{
    for(int i = 0; i < n; i++)
    {
        delete A[i];
    }
    if(rozwiazane)
    {
        for(int i = 0; i < n; i++)
        {
            delete L[i];
            delete U[i];
        }
        delete[] L;
        delete[] U;
        delete[] x;
        delete[] z;
        delete[] yObliczone;
    }
    delete[] A;
    delete[] y;
}

long double UkladRownan::liczbaLosowa(long double maksimum)
{
    //losowanie liczby
    long double liczba = ((long double) rand()/ (long double) RAND_MAX);
    liczba = liczba  * maksimum;
    int znak = rand()%2;
    if(znak == 1) // -
    {
        liczba = liczba * (-1);
    }
    return liczba;
}

void UkladRownan::losujRownanie()
{
    for(int i = 0; i < n; i++)
    {
       y[i] = liczbaLosowa(maksimum);
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            A[i][j] = liczbaLosowa(maksimum);
        }
    }
}
void UkladRownan::losujRownanieHilbert()
{
    for(int i = 0; i < n; i++)
    {
        long double suma = 0.0;
        for(int j = 0; j < n; j++)
        {
            A[i][j] = (long double) 1/ (long double)((i+1) + (j+1) - 1);
            suma += A[i][j];
        }
        y[i] = suma;
    }
}

void UkladRownan::losujRownanieBD()
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            A[i][j] = (long double) (symbolNewtona(n+i-1 + 1, i-1 +1) * symbolNewtona(n-1, n-j -1) * n)/ (long double) (i+j-1 +1+1);
        }
        y[i] = i+1;
    }

}
long long UkladRownan::symbolNewtona(int n, int k)
{
    long long wynik = 1;
    for(int i = 1; i <= k; i++)
    {
        wynik = wynik * (n - i + 1)/i;
    }
    return wynik;
}


void UkladRownan::pokaz1D(int n, long double x[], string napis)
{
    cout<<"Tablica "<<napis<<endl;
    for(int i = 0; i < n; i++)
    {
        cout<<x[i]<<endl;
    }
    cout<<endl;
}


void UkladRownan::pokaz2D(int n, long double *A[], string napis)
{
    cout<<"Tablica "<<napis<<endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout<<A[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
}

/** A = L * U **/
void UkladRownan::generujLU()
{
    /* przygotowanie pamieci */
    L = new long double*[n];
    U = new long double*[n];

    for(int i = 0; i < n; i++)
    {
        L[i] = new long double[n];
        U[i] = new long double[n];
    }
    /* inicjalizacja zmiennych */

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
            {
                L[i][j] = 1.0;
            }
            else
            {
                L[i][j] = 0.0;
            }
            U[i][j] = 0.0;
        }
    }

    /* generacja macierzy L i U */
    for(int i = 0; i < n; i++)
    {
        /** tutaj zmiany **/

        long double *P = new long double [n];
        for (int ii = 0; ii < n; ii++)
            P[ii] = ii; //Unit permutation matrix, P[N] initialized with N

        int imax;
        long double maxA, *ptr, absA;

        maxA = 0.0;
        imax = i;
        for (int k = i; k < n; k++)
        {
            absA = fabs(A[k][i]); // szukamy elementu najwiekszego w kolumnie (pod tym co juz zrobilismy)
            if (absA > maxA) {
                maxA = absA;
                imax = k;
            }
        }
        if (maxA < 0.000000001)
            cout<<"Blad prawie 0 "<<maxA<<endl;//failure, matrix is degenerate

        if (imax != i) //bedzie zamiana
        {
            cout<<"Zamiana "<<imax<<" z "<<i<<endl;
            //pivoting P
            int zamien = P[i];
            P[i] = P[imax];
            P[imax] = zamien;

            //pivoting rows of A
            ptr = A[i];
            A[i] = A[imax];
            A[imax] = ptr;

            //y tez zamienie
            long double zamien2 = y[i];
            y[i] = y[imax];
            y[imax] = zamien2;

            // L tez
            for(int a = 0; a < i; a++)
            {
                long double zamien3 = L[i][a];
                L[i][a] = L[imax][a];
                L[imax][a] = zamien3;

            }
        }

        /** tutaj koniec zmian**/

        // wiersz macierzy U
        for(int j = i; j < n; j++)
        {
            long double suma = 0.0; //0.0???
            for(int k = 0; k <= i - 1; k++)
            {
                suma += L[i][k] * U[k][j];
            }

            U[i][j] = A[i][j] - suma;
            /*cout<<"U["<<i<<"]["<<j<<"] = "<<U[i][j]<<endl;
            cout<<"suma = "<<suma<<endl<<endl; usunac*/

        }
        // kolumna macierzy L
        for(int j = i + 1; j < n; j++)
        {
            long double suma = 0.0;
            for(int k = 0; k <= i - 1; k++)
            {
                suma += L[j][k] * U[k][i];
            }
            if(U[i][i] == 0)
            {
                cout<<"Rowne 0..."<<endl;
            }
            if(fabs(U[i][i]) < 0.0001)
            {
                cout<<"Prawie 0...."<<endl;
            }
            L[j][i] = (A[j][i] - suma) / U[i][i];
        }
    }
    pokaz2D(n, A, "A");
    pokaz2D(n, L, "L");
    pokaz2D(n, U, "U");
}
/** L * z = y **/
void UkladRownan::dolnoTrojkatna()
{
    for(int i = 0; i < n; i++)
    {
        long double suma = 0.0;
        for(int j = 0; j <= i - 1; j++)
        {
            suma += L[i][j] * z[j];
        }
        z[i] = (y[i] - suma)/ L[i][i];
    }
}
/** U * x = y **/
void UkladRownan::gornoTrojkatna()
{
    for(int i = n - 1; i >= 0; i--)
    {
        long double suma = 0.0;
        for(int j = i + 1; j < n; j++)
        {
            suma += U[i][j] * x[j];
        }
        x[i] = (z[i] - suma)/U[i][i];
    }
}


void UkladRownan::rozwiaz()
{
    rozwiazane = true; // nastapila alokacja pamieci dla L, U, x, z
    generujLU();

    x = new long double [n];
    z = new long double [n];
    yObliczone = new long double[n];

    dolnoTrojkatna(); //TODO TUTAJ
    cout<<"Tablica z:"<<endl;
    for(int i = 0; i < n; i++)
    {
        cout<<z[i]<<endl;
    }
    gornoTrojkatna(); //TODO TUTAJ

    cout<<"Tablica x:"<<endl;
    for(int i = 0; i < n; i++)
    {
        cout<<x[i]<<endl;
    }
    for(int i = 0; i < n; i++)
    {
        yObliczone[i] = 0.0;
        for(int j = 0; j < n; j++)
        {
            yObliczone[i] += A[i][j]*x[j];
        }
    }
}
void UkladRownan::setMaksimum(long double maksimum)
{
    this->maksimum = maksimum;
}
int UkladRownan::getN()
{
    return this->n;
}
long double** UkladRownan::getA()
{
    return this->A;
}
long double* UkladRownan::getY()
{
    return this->y;
}
long double* UkladRownan::getX()
{
    return this->x;
}
long double* UkladRownan::getYObliczone()
{
    return this->yObliczone;
}
long double UkladRownan::getSredniBlad()
{
    long double blad = 0.0;
    for(int i = 0; i < n; i++)
    {
        blad += (yObliczone[i] - y[i]) * (yObliczone[i] - y[i]);
    }
    blad = blad / (long double) n;
    return blad;
}
long double UkladRownan::getMaksBlad()
{
    long double maksBlad = 0.0;
    long double blad = 0.0;
    for(int i = 0; i < n; i++)
    {
        blad = (yObliczone[i] - y[i]) * (yObliczone[i] - y[i]);
        if(blad > maksBlad)
        {
            maksBlad = blad;
        }
    }
    return maksBlad;
}
long double UkladRownan::getMinBlad()
{
    long double minBlad = (yObliczone[0] - y[0]) * (yObliczone[0] - y[0]);
    long double blad = 0.0;
    for(int i = 1; i < n; i++)
    {
        blad = (yObliczone[i] - y[i]) * (yObliczone[i] - y[i]);
        if(blad < minBlad)
        {
            minBlad = blad;
        }
    }
    return minBlad;
}
