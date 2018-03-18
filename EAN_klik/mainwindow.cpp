#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Macierz.h"
#include "Wyniki.h"
#include "konwersja.h"
#include<QString>
#include<sstream>
#include "rounding.h"
#include <iostream>
#include<limits>
#include<string>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Oliwia Masian EAN");
    ui->pole_maksimum->setText(toString(10.0));
    ui->pole_rozmiar->setText(QString::number(5));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_guzik_oblicz_clicked()
{
    ui->macierz->przepiszOdwrocone();
    ui->macierz->ukladRownan->rozwiaz();
    ui->macierz->rozwiazPrzedzial();
    wyniki = new Wyniki(0, ui->macierz->ukladRownan, ui->macierz->ukladRownanPrzedzial);
    wyniki->show();
}

void MainWindow::on_guzik_rozmiar_clicked()
{
    int n = ui->pole_rozmiar->text().toInt();
    long double maksimum = toLDouble(ui->pole_maksimum->text());
    if (n != ui->macierz->ukladRownan->getN())
    {
        ui->macierz->nowyUkladRownan(n, maksimum);
    }
}

void MainWindow::on_guzik_losuj_clicked()
{
    ui->macierz->losuj();
}

void MainWindow::on_guzik_maksimum_clicked()
{
    long double maksimum = toLDouble(ui->pole_maksimum->text());
    ui->macierz->ukladRownan->setMaksimum(maksimum);
    ui->macierz->losuj();
}

void MainWindow::on_guzik_Hilberta_clicked()
{
    ui->macierz->losujHilbert();
}

void MainWindow::on_guzik_BD_clicked()
{
    ui->macierz->losujBD();
}
