using namespace std;
#include <iostream>
#include <string.h>
#include "pompe.h"
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


Reservoir :: ~Reservoir()
{
	if(this->rempli)
		cout << "Réservoir rempli détruit" << endl;
	else
		cout << "Réservoir vide détruit" << endl;
}

 /*Méthode test
int main()
{
	Reservoir r1(true); Reservoir r2(false);
	
	r1.toString();
	r2.toString();
	r1.vidange();
	
	r1.toString();
	r2.toString();
	
	return 0;
}*/
	
