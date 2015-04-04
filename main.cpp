#include <iostream>
#include <string.h>
#include "reservoir.h"
#include "pompe.h"
#include "vanne.h"
#include "main.h"
#include "mainwindow.h"
#include "fenetrepilote.h"
#include "avion.h"
#include <QApplication>
#include <QWidget>


using namespace std;


/* 
 * 
 * Blah Blah
 * 
 */
	

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Avion* a = new Avion();
    MainWindow fenetre1(a);
    fenetrePilote fenetre2(a);
    fenetre1.show();
    fenetre2.show();

    return app.exec();
}
