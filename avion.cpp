#include "avion.h"

Avion::Avion()
{
    for(int i = 0; i < 3; i++)
        this->R[i] = new Reservoir(true);
    for(int i = 0; i < 5; i++)
        this->V[i] = new Vanne();
}

void Avion::reset()
{
    for(int i = 0; i < 3; i++)
        this->R[i].reset();
    for(int i = 0; i < 5; i++)
        this->V[i].fermer();
}





// IMPLEMENTER LES GETTERS/SETTERS
