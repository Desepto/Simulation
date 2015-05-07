#include "avion.h"
#include "identification.h"
#include <QApplication>
#include <QWidget>


using namespace std;

/* 
 * Ouverture de l'application
 * Lancement d l'avion
 * Ouverture de la BDD
 * Ouverture de la fenêtre d'identification
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
