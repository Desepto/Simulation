#include <iostream>
#include <string.h>
#include "reservoir.h"
#include "pompe.h"
#include "vanne.h"
#include "main.h"
#include "mainwindow.h"
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
    MainWindow w(a);
    w.show();
	Reservoir r(true);
	Pompe p;
    Vanne v;

    v.fermer();
	
    return app.exec();
}
