#ifndef AVION_H
#define AVION_H

#include "reservoir.h"
#include "bool.h"

class Avion
{
private:
    Reservoir r1;
    Reservoir r2;
    Reservoir r3;
    bool v1;
    bool v2;
    bool v3;
    bool v4;
    bool v5;

public:
    Avion();


    /* Getters */
    bool getR1();
    bool getR2();
    bool getR3();
    int getP1(Reservoir r);
    int getP2(Reservoir r);
    bool getV1();
    bool getV2();
    bool getV3();
    bool getV4();
    bool getV5();

    /* Setters */
    void setR1(bool val);
    void setR2(bool val);
    void setR3(bool val);
    void setP1(Reservoir r, int val);
    void setP2(Reservoir r, int val);
    void setV1(bool val);
    void setV2(bool val);
    void setV3(bool val);
    void setV4(bool val);
    void setV5(bool val);

};

#endif // AVION_H
