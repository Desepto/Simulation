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

    QSqlDatabase BDD;
    QString path = QCoreApplication::applicationDirPath();
    path += "/Simulation.sqlite";
    BDD = QSqlDatabase::addDatabase("QSQLITE");
    BDD.setDatabaseName(path);


    Identification fenetre3(a, BDD);
    fenetre3.show();

    return app.exec();
}
