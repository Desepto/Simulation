#ifndef FENETREPILOTE_H
#define FENETREPILOTE_H

#include <QMainWindow>
#include "avion.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class fenetrePilote;
}

class fenetrePilote : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit fenetrePilote(Avion* a, QWidget *parent = 0);
    ~fenetrePilote();
    void addfenetre(MainWindow* f1);
    void updateFenetre();

public slots:

    void closeEvent(QCloseEvent *);
    void modifV12();
    void modifV23();
    void modifV21();
    void modifV31();
    void modifV32();
    void modifP12();
    void modifP22();
    void modifP32();

private:
    Ui::fenetrePilote *ui;
    MainWindow* f1;
    Avion* a;
};

#endif // FENETREPILOTE_H
