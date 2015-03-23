#ifndef AVION_H
#define AVION_H

#include "reservoir.h"
#include "vanne.h"
#include "qwidget.h"

class Avion : QWidget
{
private:
    Reservoir tabReser[3];
    Vanne tabVanne[5];

public:
    Avion();
};

#endif // AVION_H
