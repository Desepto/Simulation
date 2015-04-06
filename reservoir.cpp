using namespace std;
#include <iostream>
#include <string.h>
#include "vanne.h"
#include "reservoir.h"


Reservoir :: Reservoir() : p1(1), p2(0)
{
    this->rempli = false;
}

Reservoir :: Reservoir(bool remplissage) : p1(1), p2(0)
{
	this->rempli = remplissage;
}


ostream & operator << (ostream& os, Reservoir r)
{
    if(r.getRempli())
        os << "Ceci est un Réservoir rempli" << endl;
    else
        os << "Ceci est un Réservoir vide" << endl;

    return os;
}

// Vidange et remplir sont des setteurs : Plus clair mais reviens à 
//avoir la variable en public

void Reservoir :: vidange()
{
	this->rempli = false;
}

bool Reservoir :: getRempli()
{
    return this->rempli;
}

QPalette Reservoir::getCouleur()
{
    if(this->rempli)
        return Qt::green;
    else
        return Qt::blue;
}

Pompe Reservoir::getPompe1()
{
    return this->p1;
}

Pompe Reservoir::getPompe2()
{
    return this->p2;
}

Reservoir :: ~Reservoir()
{
	if(this->rempli)
		cout << "Réservoir rempli détruit" << endl;
	else
        cout << "Réservoir vide détruit" << endl;
}

void Reservoir::reset()
{
    this->rempli = true;
    this->p1.marche();
    this->p2.marche();
}

