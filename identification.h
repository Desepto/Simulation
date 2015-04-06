#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include <QDialog>
#include <QtSql>
#include <QFileInfo>
#include "mainwindow.h"
#include "fenetrepilote.h"

namespace Ui {
class Identification;
}

class Identification : public QDialog
{
    Q_OBJECT
    
public:
    explicit Identification(Avion *a,QWidget *parent = 0);
    ~Identification();
    
private slots:
    void on_validation_accepted();

    void on_validation_rejected();

private:
    Ui::Identification *ui;
    Avion *a;
    QSqlDatabase BDD;
};

#endif // IDENTIFICATION_H