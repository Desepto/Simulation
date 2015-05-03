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

Reservoir Avion :: getReservoir(int i)
{
    return R[i];
}

Vanne Avion :: getVanne(int i)
{
    return V[i];
}

int Avion :: getMoteur(int i, int j)
{
    return moteur[i][j];
}

void Avion :: setMoteur(int i, int j, int alimente)
{
    moteur[i][j] = alimente;
}

int Avion :: nbReservoirVidange()
{
    int res = 0;
    for(int i = 0 ; i < 3 ; i++)
        if(R[i].getVidange())
            res++;
    return res;
}

bool Avion :: peutFonctionner()
{
    if(nbReservoirVidange() == 3)
        return false;
    int pompeFonctionnelle = 0;
    int j;
    for(j = 0 ; j < 3 ; j++)
    {
        if(R[j].getPompe1().isMarche())
            pompeFonctionnelle++;
        if(R[j].getPompe2().isMarche())
            pompeFonctionnelle++;
    }
    if(pompeFonctionnelle < 3)
        return false;
    else
        return true;
}

bool Avion :: actionNecessaire()
{
    if(!peutFonctionner())
    {
        cout << "L'avion ne peut plus fonctionner!" << endl;
        return false;
    }
    int pompeAllumee = 0;
    int pompeSecAllumee = 0;
    int nbMoteurAlimente = 0;
    int nbResVide = nbReservoirVidange();
    for(int j = 0; j < 3 ; j++){
        for(int i = 0 ; i < 3 ; i++)
        {
            if(moteur[j][i] == 1)
                nbMoteurAlimente++;
        }
        if(nbMoteurAlimente != 3)
            return true;
        if(R[j].getPompe1().getEtat() == 1)
        {
            pompeAllumee++;
            if(!R[j].getRempli())
                return true;
        }
        if(R[j].getPompe2().getEtat() == 1)
        {
            pompeAllumee++;
            pompeSecAllumee++;
            if(!R[j].getRempli())
                return true;
        }
        if(pompeAllumee > 3)
            return true;
    }
    if( nbResVide == 0 && ( !V[0].getOuvert() || !V[1].getOuvert() ) )
        return true;
    if( pompeSecAllumee == 0 && ( !V[2].getOuvert() || !V[3].getOuvert() || !V[4].getOuvert() ) )
        return true;
    return false;
}


