#include <iostream>
#include <string.h>
#include "reservoir.h"
#include "pompe.h"
#include "vanne.h"
#include "main.h"
using namespace std;


/* 
 * 
 * 
 * 
 */
	

int main(int argc, char **argv)
{
	Reservoir r(true);
	Pompe p;
    Vanne v;

    v.fermer();
	
	return 0;
}
