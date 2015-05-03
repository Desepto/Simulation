#include <iostream>
#include <string.h>
#include "reservoir.h"
#include "pompe.h"
#include "vanne.h"
#include "main.h"
#include "mainwindow.h"
#include "fenetrepilote.h"
#include "avion.h"
#include "identification.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>


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
  //  MainWindow fenetre1(a);
  //  MainWindow* f1; f1 = fenetre1;
   // fenetrePilote fenetre2(a);
   // fenetrePilote* f2 = fenetre2;

    QSqlDatabase BDD;
    QString path = QCoreApplication::applicationDirPath();
    path += "./Simulation.sqlite";
    BDD = QSqlDatabase::addDatabase("QSQLITE");
    BDD.setDatabaseName(path);


    Identification fenetre3(a, BDD);
    //fenetre1.show();
    //fenetre2.show();
    fenetre3.show();

    return app.exec();
}
