#ifndef AVION_H
#define AVION_H

#include "reservoir.h"
#include "vanne.h"

class Avion
{
private:
    Reservoir R[3];
    Vanne V[5];

public:
    Avion();

    void reset();


    friend class MainWindow;
    friend class fenetrePilote;

};

#endif // AVION_H
