using namespace std;
#include <iostream>
#include <string.h>
#include "pompe.h"

Pompe :: Pompe()
{
	this->etat = -1;
}

Pompe :: Pompe(int etat)
{
	this->etat = etat;
}

//Ce sont des setteurs : Plus clair mais reviens à 
//avoir la variable en public

void Pompe :: panne()
{
	this->etat = -1;
}

void Pompe :: arret()
{
	if(this->etat != -1)
		this->etat = 0;
}

void Pompe::resetp2()
{
    this->etat = 0;
}

void Pompe :: marche()
{
	if(this->etat != -1)
		this->etat = 1;
}

int Pompe :: getEtat() const
{
    return this->etat;
}

int Pompe::getEnFonction()
{
    if(this->etat == -1)
        return 0;
    else
        return 1;
}

bool Pompe::isMarche()
{
    if(this->etat == -1)
        return false;
    else
        return true;
}

QPalette Pompe::getCouleur()
{
    if(this->etat == -1)
        return Qt::blue;
    else if(!this->etat)
        return Qt::red;
    else
        return Qt::green;
}


ostream & operator << (ostream & os, Pompe p)
{
    if(p.getEtat() == -1)
        os << "Ceci est une pompe en panne" << endl;
    else if(p.getEtat() == 0)
        os << "Ceci est une pompe à l'arrêt" << endl;
    else
        os << "Ceci est une pompe en marche" << endl;

    return os;
}

Pompe :: ~Pompe()
{
	if(this->etat == -1)
		cout << "Destruction d'une pompe en panne" << endl;
	else if(this->etat == 0)
		cout << "Destruction d'une pompe à l'arrêt" << endl;
	else
		cout << "Destruction d'une pompe en marche" << endl;
}


