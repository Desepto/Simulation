#include "avion.h"

/*
  Classe stockant tous les élements de l'avion (Réservoirs/vannes/pompes) ainsi que quelques méthodes pour les manipuler
  */

// Il n'y a qu'un constructeur par défaut car un avion commence toujours dans un même état

Avion::Avion()
{
    for(int i = 0; i < 3; i++)
        this->R[i] = new Reservoir(true);
    for(int i = 0; i < 5; i++)
        this->V[i] = new Vanne();

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            if(i == j)
                moteur[i][j] = 1;
            else
                moteur[i][j] = 0;
        }
}

//Remise à zéro de l'avion lors d'une réinitialisation de l'utilisateur

void Avion::reset()
{
    for(int i = 0; i < 3; i++)
        this->R[i].reset();
    for(int i = 0; i < 5; i++)
        this->V[i].ouvrir();
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            if(i == j)
                moteur[i][j] = 1;
            else
                moteur[i][j] = 0;
        }

}

//Fonction utilisée pour simplifier du code dans udpateFenetre() de mainwindow

QPixmap Avion::getCouleurAlimMoteur(int i, int j)
{
    QPixmap vert(":/icones/vert");
    QPixmap rouge(":/icones/rouge");

    if(this->moteur[i][j])
        return vert;
    else
        return rouge;
}

//Fonction utilisée pour simplifier du code dans udpateFenetre() de mainwindow

QPalette Avion::isAlimente(int j)
{
    for(int i = 0; i < 3; i++)
    {

        if(this->moteur[i][j])
            return Qt::green;
        else if(i == 2)
            return Qt::red;
    }
}

//Fonction renvoyant le nombre de réservoirs vidangés

int Avion :: nbReservoirVidange()
{
    int res = 0;
    for(int i = 0 ; i < 3 ; i++)
        if(R[i].getVidange())
            res++;
    return res;
}

//Renvoit un boolean indiquant si il est encore possible de réparer l'avion
// L'avion est réparable ssi il y a au moins 3 pompes alimentables fonctionnelles

bool Avion :: peutFonctionner()
{
    if(nbReservoirVidange() == 3)
        return false;
    int pompeFonctionnelle = 0;
    int j;
    for(j = 0 ; j < 3 ; j++)
    {
        if(R[j].getPompe1().isMarche())
            pompeFonctionnelle++;
        if(R[j].getPompe2().isMarche())
            pompeFonctionnelle++;
    }
    if(pompeFonctionnelle < 3)
        return false;
    else
        return true;
}

//Fonction indiquant si une action du pilote est nécessaire pour revenir dans un état normal

bool Avion :: actionNecessaire()
{
    if(!peutFonctionner())
    {
        return false;
    }
    int pompeAllumee = 0;
    int pompeSecAllumee = 0;
    int nbMoteurAlimente = 0;
    int nbResVide = nbReservoirVidange();
    for(int j = 0; j < 3 ; j++){
        for(int i = 0 ; i < 3 ; i++)
        {
            if(moteur[j][i] == 1)
                nbMoteurAlimente++;
        }
        if(R[j].getPompe1().getEtat() == 1)
        {
            pompeAllumee++;
            if(!R[j].getRempli())
                return true;
        }
        if(R[j].getPompe2().getEtat() == 1)
        {
            pompeAllumee++;
            pompeSecAllumee++;
            if(!R[j].getRempli())
                return true;
        }
        if(pompeAllumee > 3)
            return true;
    }
    if(nbMoteurAlimente != 3)
        return true;
    if( nbResVide == 0 && ( !V[0].getOuvert() || !V[1].getOuvert() ) )
        return true;
    if( pompeSecAllumee == 0 && ( !V[2].getOuvert() || !V[3].getOuvert() || !V[4].getOuvert() ) )
        return true;
    return false;
}


