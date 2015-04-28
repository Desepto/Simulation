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
        return QPixmap(":/icones/vert");
    else
        return QPixmap(":/icones/rouge");
}

QPalette Vanne::getCouleur()
{
    if(this->ouvert)
        return Qt::green;
    else
        return Qt::red;
}

Vanne :: ~Vanne()
{
	if(this->ouvert)
		cout << "Vanne ouverte détruite" << endl;
	else
		cout << "Vanne fermée détruite" << endl;
}
