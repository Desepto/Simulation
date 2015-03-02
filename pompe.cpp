#include <iostream>
#include <string.h>
#include "pompe.h"
using namespace std;

Pompe :: Pompe()
{
	this->etat = -1;
}

Pompe :: Pompe(int etat)
{
	this->etat = etat;
}

Pompe :: Pompe(const Pompe &p)
{
	this->etat = p.etat;
}

Pompe Pompe :: operator=(const Pompe &p)
{
	this->etat = p.etat;
	return *this;
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

void Pompe :: marche()
{
	if(this->etat != -1)
		this->etat = 1;
}

int Pompe :: getEtat()
{
	return this->etat;
}

void Pompe :: toString()
{
	if(this->etat == -1)
		cout << "Ceci est une pompe en panne" << endl;
	else if(this->etat == 0)
		cout << "Ceci est une pompe à l'arrêt" << endl;
	else
		cout << "Ceci est une pompe en marche" << endl;
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

/* Méthode test
int main()
{
	
	
	Pompe p1(0), p2(1), p3(-1);
	
	cout << "Pompe p1 " ; p1.toString();
	cout << "Pompe p2 " ; p2.toString();
	cout << "Pompe p3 " ; p3.toString();
	
	p1.marche();
	p2.arret();
	p3.marche();
	p3.arret();
	
	
	cout << "Pompe p1 " ; p1.toString();
	cout << "Pompe p2 " ; p2.toString();
	cout << "Pompe p3 " ; p3.toString();
	
	
	return 1;
}
* */

