#include <iostream>
#include <string.h>
#include "vanne.h"
using namespace std;

Vanne :: Vanne()
{
    this->ouvert = true;
}

Vanne :: Vanne(bool ouverture)
{
	this->ouvert = ouverture;
}

ostream & operator << (ostream& os, Vanne v)
{
    if(v.getOuvert())
        os << "Ceci est une vanne ouverte" << endl;
    else
        os << "Ceci est une vanne fermée" << endl;

    return os;
}

// Vidange et remplir sont des setteurs : Plus clair

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

QPixmap Vanne::getpixmap()
{
    if(this->ouvert)
        return QPixmap(":/icones/rouge");
    else
        return QPixmap(":/icones/vert");
}

QPalette Vanne::getCouleur()
{
    if(this->ouvert)
        return Qt::red;
    else
        return Qt::green;
}

Vanne :: ~Vanne()
{
	if(this->ouvert)
		cout << "Vanne ouverte détruite" << endl;
	else
		cout << "Vanne fermée détruite" << endl;
}
