#ifndef RESERVOIR_H
#define RESERVOIR_H
using namespace std;
#include <iostream>
#include "pompe.h"
#include <QPalette>

class Reservoir
{
private :
	bool rempli;
    Pompe p1;
    Pompe p2;
	
public :
	Reservoir();
    Reservoir(bool remplissage);

    friend ostream & operator << (ostream& os, Reservoir r);
    void vidange();
    bool getRempli();
    QPalette getCouleur();
	
    Pompe getPompe1();
    Pompe getPompe2();

    void reset();
	
	~Reservoir();
	
};

#endif
