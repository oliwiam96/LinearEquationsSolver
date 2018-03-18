#include "mainwindow.h"
#include <QApplication>

#include<iostream>
#include<sstream>
#include<QString>

#include<mpfr.h>
#include<boost/numeric/interval.hpp>
#include "rounding.h"

using namespace std;

/*int sign_polynomial(double x, double P[], int sz) {
  using namespace boost::numeric;
  using namespace interval_lib;
  typedef interval<double> I_aux;

  I_aux::traits_type::rounding rnd;
  typedef unprotect<I_aux>::type I;
  I* m = new I();
  m->set(2.3, 2.5);

  I y = P[sz - 1];
  for(int i = sz - 2; i >= 0; i--)
    y = y * x + P[i];

  using namespace compare::certain;
  if (y > 0.) return 1;
  if (y < 0.) return -1;
  return 0;
}*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    cout.precision(50);
    /*cout<<returnLow("1.1")<<endl;
    cout<<returnUp("1.1")<<endl;
    using namespace boost::numeric;
    using namespace interval_lib;
    typedef interval<long double> I_aux;

    I_aux::traits_type::rounding rnd;
    typedef unprotect<I_aux>::type I;
    I* m = new I();
    I* x = new I [3];
    x[0].set((long double) 1.1, 2.7);
    cout<<x[0].lower()<<endl;
    long double  mat = 11;
    mat = mat / (long double) 10; //ciekawe
    cout<<mat<<endl;
    m->set(2.3, 2.5);
    cout<<m->upper()<<endl;*/

    return a.exec();
}


