#include "Wyniki.h"
#include "ui_wyniki.h"

#include<QString>
#include<QScrollBar>
#include "UkladRownan.h"
#include "konwersja.h"

Wyniki::Wyniki(QWidget *parent, UkladRownan* ukladRownan, UkladRownanPrzedzial *ukladRownanPrzedzial) :
    QDialog(parent),
    ui(new Ui::Wyniki)
{
    this->ukladRownan = ukladRownan;
    this->ukladRownanPrzedzial = ukladRownanPrzedzial;
    ui->setupUi(this);
    setWindowTitle("Wyniki");

    ui->etykieta_blad->setText(toString(ukladRownan->getSredniBlad()));
    ui->etykieta_blad2->setText(toString(ukladRownanPrzedzial->getSredniBlad()));
    ui->min_blad_poz->setText(toString(ukladRownan->getMinBlad()));
    ui->maks_blad_poz->setText(toString(ukladRownan->getMaksBlad()));
    ui->min_blad_przedz->setText(toString(ukladRownanPrzedzial->getMinBlad()));
    ui->maks_blad_przedz->setText(toString(ukladRownanPrzedzial->getMaksBlad()));

    QString* x = new QString("");
    for(int i = 0; i < ukladRownan->getN(); i++)
    {
       *x = *x +  "x["+ QString::number(i+1) +"] = " + toString(ukladRownan->getX()[i]);
       *x = *x + '\n';
    }
    QString* y = new QString("");
    for(int i = 0; i < ukladRownan->getN(); i++)
    {
       *y = *y +  "y["+ QString::number(i+1) +"] = " + toString(ukladRownan->getY()[i]);
       *y = *y + '\n';
    }
    QString* yObliczone = new QString("");
    for(int i = 0; i < ukladRownan->getN(); i++)
    {
       *yObliczone = *yObliczone +  "y*["+ QString::number(i+1) +"] = " + toString(ukladRownan->getYObliczone()[i]);
       *yObliczone = *yObliczone + '\n';
    }
    QString* xPrzedzial = new QString("");
    for(int i = 0; i < ukladRownan->getN(); i++)
    {
       *xPrzedzial = *xPrzedzial+  "x_lewy["+ QString::number(i+1) +"] = " + toString(ukladRownanPrzedzial->getX()[i].lower());
       *xPrzedzial= *xPrzedzial + '\n';
    }
    QString* xPrzedzialprawy = new QString("");
    for(int i = 0; i < ukladRownan->getN(); i++)
    {
       *xPrzedzialprawy = *xPrzedzialprawy+  "x_prawy["+ QString::number(i+1) +"] = " + toString(ukladRownanPrzedzial->getX()[i].upper());
       *xPrzedzialprawy= *xPrzedzialprawy + '\n';
    }
    QString* xPrzedzialSzerokosc = new QString("");
    for(int i = 0; i < ukladRownan->getN(); i++)
    {
       *xPrzedzialSzerokosc = *xPrzedzialSzerokosc+  "x_szerokosc["+ QString::number(i+1) +"] = " +
                toString(ukladRownanPrzedzial->getX()[i].upper() - ukladRownanPrzedzial->getX()[i].lower());
       *xPrzedzialSzerokosc = *xPrzedzialSzerokosc + '\n';
    }


    ui->textBrowser->setText(*x);
    ui->textBrowser_2->setText(*y);
    ui->textBrowser_3->setText(*yObliczone);
    ui->textBrowser_4->setText(*xPrzedzial);
    ui->textBrowser_5->setText(*xPrzedzialprawy);
    ui->textBrowser_6->setText(*xPrzedzialSzerokosc);

}

Wyniki::~Wyniki()
{
    delete ui;
}
