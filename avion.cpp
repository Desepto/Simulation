#include "avion.h"

Avion::Avion()
{
    this->r1 = new Reservoir(true);
    this->r2 = new Reservoir(true);
    this->r3 = new Reservoir(true);
    this->v1 = new Vanne();
    this->v2 = new Vanne();
    this->v3 = new Vanne();
    this->v4 = new Vanne();
    this->v5 = new Vanne();


}
