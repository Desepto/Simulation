#include <iostream>
#include <string.h>
#include "vanne.h"
using namespace std;

Vanne :: Vanne()
{
	this->ouvert = false;
}

Vanne :: Vanne(bool ouverture)
{
	this->ouvert = ouverture;
}

Vanne :: Vanne(const Vanne &r)
{
	this->ouvert = r.ouvert;
}

Vanne Vanne :: operator=(const Vanne &r)
{
	this->ouvert = r.ouvert;
	return *this;
}

// Vidange et remplir sont des setteurs : Plus clair mais reviens à 
//avoir la variable en public

void Vanne :: fermer()
{
	this->ouvert = false;
}

void Vanne :: ouvrir()
{
	this->ouvert = true;
}

bool Vanne :: getOuvert()
{
	return this->ouvert;
}

void Vanne :: toString()
{
	if(this->ouvert)
		cout << "Ceci est une vanne ouverte" << endl;
	else
		cout << "Ceci est une vanne fermée" << endl;
}

Vanne :: ~Vanne()
{
	if(this->ouvert)
		cout << "Vanne ouverte détruite" << endl;
	else
		cout << "Vanne fermée détruite" << endl;
}

/*
int main()
{
	Vanne v1, v2(true);
	
	cout << "Vanne 1 : "; v1.toString();
	cout << "Vanne 2 : "; v2.toString();
	
	v1.ouvrir(); v2.fermer();
	
	cout << "Vanne 1 : "; v1.toString();
	cout << "Vanne 2 : "; v2.toString();
	
	v1 = v2;
	
	cout << "Vanne 1 : "; v1.toString();
	cout << "Vanne 2 : "; v2.toString();
	
	
	
	return 1;
}
*/
