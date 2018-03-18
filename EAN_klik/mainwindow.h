#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Wyniki.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_guzik_oblicz_clicked();

    void on_guzik_rozmiar_clicked();

    void on_guzik_losuj_clicked();

    void on_guzik_maksimum_clicked();
    
    void on_guzik_Hilberta_clicked();

    void on_guzik_BD_clicked();

private:
    Ui::MainWindow *ui;
    Wyniki *wyniki;
};

#endif // MAINWINDOW_H
