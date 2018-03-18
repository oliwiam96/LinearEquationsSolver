#ifndef WYNIKI_H
#define WYNIKI_H

#include <QDialog>
#include "UkladRownan.h"
#include "UkladRownanPrzedzial.h"

namespace Ui {
class Wyniki;
}

class Wyniki : public QDialog
{
    Q_OBJECT

public:
    explicit Wyniki(QWidget *parent = 0, UkladRownan* ukladRownan = NULL, UkladRownanPrzedzial* ukladRownanPrzedzial=NULL);
    ~Wyniki();

private:
    Ui::Wyniki *ui;
    UkladRownan *ukladRownan;
    UkladRownanPrzedzial *ukladRownanPrzedzial;
};

#endif // WYNIKI_H
