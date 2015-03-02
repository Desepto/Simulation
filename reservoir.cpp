#include <iostream>
#include <string.h>
#include "reservoir.h"
using namespace std;

Reservoir :: Reservoir()
{
	this->rempli = false;
}

Reservoir :: Reservoir(bool remplissage)
{
	this->rempli = remplissage;
}

Reservoir :: Reservoir(const Reservoir &r)
{
	this->rempli = r.rempli;
}

Reservoir Reservoir :: operator=(const Reservoir &r)
{
	this->rempli = r.rempli;
	return *this;
}

// Vidange et remplir sont des setteurs : Plus clair mais reviens à 
//avoir la variable en public

void Reservoir :: vidange()
{
	this->rempli = false;
}

void Reservoir :: remplir()
{
	this->rempli = true;
}

bool Reservoir :: getRempli()
{
	return this->rempli;
}

void Reservoir :: toString()
{
	if(this->rempli)
		cout << "Ceci est un Réservoir rempli" << endl;
	else
		cout << "Ceci est un Réservoir vide" << endl;
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
	
