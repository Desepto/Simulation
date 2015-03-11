#ifndef RESERVOIR_H
#define RESERVOIR_H
using namespace std;
#include <iostream>
#include "pompe.h"

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
	void toString();
	
    Pompe getPompe();

	
	
	~Reservoir();
	
};

#endif
