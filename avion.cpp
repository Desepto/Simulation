#include "avion.h"

Avion::Avion()
{
    for(int i = 0; i < 3; i++)
        this->R[i] = new Reservoir(true);
    for(int i = 0; i < 5; i++)
        this->V[i] = new Vanne();

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            if(i == j)
                moteur[i][j] = 1;
            else
                moteur[i][j] = 0;
        }
}

void Avion::reset()
{
    for(int i = 0; i < 3; i++)
        this->R[i].reset();
    for(int i = 0; i < 5; i++)
        this->V[i].fermer();
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            if(i == j)
                moteur[i][j] = 1;
            else
                moteur[i][j] = 0;
        }

}

QPixmap Avion::getCouleurAlimMoteur(int i, int j)
{
    QPixmap vert(":/icones/vert");
    QPixmap rouge(":/icones/rouge");

    if(this->moteur[i][j])
        return vert;
    else
        return rouge;
}

QPalette Avion::isAlimente(int i)
{
    for(int j = 0; j < 3; j++)
    {

        if(this->moteur[i][j])
            return Qt::green;
        else if(j == 2)
            return Qt::red;
    }

}





// IMPLEMENTER LES GETTERS/SETTERS
