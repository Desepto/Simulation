using namespace std;
#include "identification.h"
#include "ui_identification.h"
#include <iostream>
#include <QMessageBox>

Identification::Identification(Avion *a, QSqlDatabase BDD, QWidget *parent) :
    QDialog(parent), ui(new Ui::Identification)
{
    this->parent = parent;
    this->BDD = BDD;
    ui->setupUi(this);
    //Chemin BDD
    QString path = QCoreApplication::applicationDirPath();
    qDebug() << path;
    path += "/Simulation.sqlite";
    qDebug() << path;

    if(this->parent == 0)
    {
    //init BDD
    QFileInfo verifier_BDD(path);

        if(!verifier_BDD.isFile())
        {
            QMessageBox::warning(this, "Warning", "Base de donnée inexistante");
            this->close();
        }
        else
        {
            if(BDD.open()){}
            else
            {
                QMessageBox::warning(this, "Warning", "Base de donnée non chargée");
                this->close();
            }
        }
    }
    this->a = a;
}


Identification::~Identification()
{
    delete ui;
}

void Identification::on_validation_accepted()
{
    printf("bite 2\n");
    bool etapeSuivante = false;
    //Inscription
    if(ui->inscription->isChecked())
    {
        if(!BDD.isOpen())
            QMessageBox::warning(this, "Echec de l'ouverture", "Pas de BDD");

        QSqlQuery rqt;

        rqt.exec("SELECT Nom FROM User Where Nom='" + ui->Nom->text() + "'");
        if(!rqt.next())
        {//Si il n'y a rien
            if(rqt.exec("INSERT INTO User (Nom, Mdp) VALUES('"+ ui->Nom->text() +"', '"+ ui->Mdp->text() +"')"))
            {
                QMessageBox::warning(this, "Réussite !", "Inscription réussie");
                etapeSuivante = true;
            }
            else
                QMessageBox::warning(this, "Echec !", "L'inscription a raté");
        }
        else
            QMessageBox::warning(this, "Echec !", "Nom déjà utilisé !");


        //Rajouter l'user dans la base si il y est pas déjà (comme ta mère)

    }
    else
    {
        if(!BDD.isOpen())
            QMessageBox::warning(this, "Echec de l'ouverture", "Pas de BDD");
        QSqlQuery rqt;
        if(rqt.exec("SELECT Nom, Mdp FROM User WHERE Nom='" + ui->Nom->text() + "' AND Mdp='" + ui->Mdp->text() + "'"))
        {
            if(!rqt.next())
                QMessageBox::warning(this, "Echec !", "Mauvais Nom ou mot de passe");
            else
                etapeSuivante = true;

        }
        //Vérifier si l'user correspond
    }
    if(etapeSuivante)
    {
        MainWindow* fenetre1 = new MainWindow(this->a, ui->Nom->text(), this->BDD);
        fenetrePilote* fenetre2 = new fenetrePilote(this->a);
        fenetre1->addfenetre(fenetre2);
        fenetre2->addfenetre(fenetre1);
        fenetre1->show();
        fenetre2->show();

        this->close();
        if(this->parent != 0)
            this->parent->close();
    }



}

void Identification::on_validation_rejected()
{
    this->close();
}
