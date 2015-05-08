#include "affichertexte.h"
#include "ui_affichertexte.h"

/*
  Classe permettant d'afficher une fenêtre avec du texte et un bouton de fermeture.
  Utilisée pour afficher les fenetres d'aide et d'affichage des scores.
*/

afficherTexte::afficherTexte(int aAfficher, QSqlDatabase BDD, QString nom, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::afficherTexte)
{
    ui->setupUi(this);
    if(aAfficher == 1) // AFFICHAGE DE L'AIDE
    {
        this->setWindowTitle("Aide");
        QString aEcrire = "Pour lancer la simulation cliquez sur \"Lancer Simulation\" \n";
        aEcrire += "Pour arreter la simulation et sauvegarder votre score cliquez sur \"Stopper Simulation\" \n";
        aEcrire += "Pour lancer le mechanisme de pannes automatiques cliquez sur \"Pannes Automatiques\" \n";
        aEcrire += "Attention a ne pas lancer les pannes automatiques alors que la simulation n'est pas lancee ! \n";
        aEcrire += "Pour resoudre les problemes de l'avion cliquez sur les boutons de la fenetre Pilote \n";
        aEcrire += "Pour etre dans un etat stable un avion ne doit avoir que 3 pompes fournissant du carburant d'allumees \n";
        aEcrire += "Bonne chance et que la force soit avec vous ! \n\n\n";
        aEcrire += "Legende : \n";
        aEcrire += "- Vert : en fonctionnement/approvisione en carburant\n";
        aEcrire += "- Rouge : eteint/non-approvisione en carburant\n";
        aEcrire += "- Bleu : en panne\n";
        this->ui->texte->setText(aEcrire);
    }
    if(aAfficher == 2) // AFFICHAGE DES SCORES
    {

        this->setWindowTitle("Scores");
        QString aEcrire = "Dix derniers scores pour ", usrId;
        aEcrire += nom + " : \n";
        QSqlQuery rqt;
        if(rqt.exec("SELECT UsrId FROM User Where Nom='" + nom + "'"))
        { // Récupération de l'id utilisateur
            rqt.next();
            usrId.setNum(rqt.value(0).toInt(), 10);
        }

        rqt.exec("SELECT Score FROM Score WHERE IdUser='"+ usrId +"'");
        int max = 0, total = 0, nbScores = 0, temp = 0;

        while(rqt.isValid() && rqt.next())
        { // parcours de tous les résultats
            temp = rqt.value(0).toInt();
            if( nbScores < 10)
            { // affichage des 10 derniers
            aEcrire += QString::number(nbScores) + ") ";
            aEcrire += QString::number(temp);
            aEcrire += "\n\n";
            }
            if(temp > max)
                max = temp;
            total += temp;
            nbScores++;
        }
        //Affichage du max + la moyenne
        if(nbScores == 0)
            aEcrire += "Aucun score enregistre";
        else
        {
            aEcrire += "Meilleur score : " + QString::number(max) + " ! \n\n";
            aEcrire += "Moyenne des scores : " + QString::number((double) (total / nbScores)) +" ! \n";
        }

    this->ui->texte->setText(aEcrire);
    }

}

afficherTexte::~afficherTexte()
{
    delete ui;
}

void afficherTexte::on_pushButton_clicked()
{
    this->close();
}
