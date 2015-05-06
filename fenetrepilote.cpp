#include "fenetrepilote.h"
#include "ui_fenetrepilote.h"

fenetrePilote::fenetrePilote(Avion* a,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fenetrePilote)
{
    ui->setupUi(this);
    this->a = a;

    connect(ui->V12, SIGNAL(clicked()), this, SLOT(modifVT12()));
    connect(ui->V23, SIGNAL(clicked()), this, SLOT(modifVT23()));
    connect(ui->V21, SIGNAL(clicked()), this, SLOT(modifV12()));
    connect(ui->V31, SIGNAL(clicked()), this, SLOT(modifV13()));
    connect(ui->V32, SIGNAL(clicked()), this, SLOT(modifV23()));
    connect(ui->P12, SIGNAL(clicked()), this, SLOT(modifP12()));
    connect(ui->P22, SIGNAL(clicked()), this, SLOT(modifP22()));
    connect(ui->P32, SIGNAL(clicked()), this, SLOT(modifP32()));

    this->move(875,50);
}

fenetrePilote::~fenetrePilote()
{
    cout << "Destruction fenetre pilote" << endl;
    delete ui;
}

void fenetrePilote::updateFenetre(bool premierAppel) // A tester
{

    this->ui->F1->setPalette(this->a->V[0].getCouleur());
    this->ui->F2->setPalette(this->a->V[1].getCouleur());
    this->ui->F6->setPalette(this->a->V[2].getCouleur());
    this->ui->F7->setPalette(this->a->V[3].getCouleur());
    this->ui->F8->setPalette(this->a->V[4].getCouleur());

    this->ui->F3->setPalette(this->a->R[0].getPompe2().getCouleur());
    this->ui->F4->setPalette(this->a->R[1].getPompe2().getCouleur());
    this->ui->F5->setPalette(this->a->R[2].getPompe2().getCouleur());

    this->ui->P12->setEnabled(this->a->R[0].getPompe2().isMarche());
    this->ui->P22->setEnabled(this->a->R[1].getPompe2().isMarche());
    this->ui->P32->setEnabled(this->a->R[2].getPompe2().isMarche());

   if(premierAppel)
    {
        printf("test\n");
        this->f1->updateFenetre(false);
    }

}

void fenetrePilote::addfenetre(MainWindow *f1)
{
    this->f1 = f1;
}



void fenetrePilote::closeEvent(QCloseEvent *)
{
    this->f1->close();
    this->close();
}

void fenetrePilote::modifVT12()
{

    if(a->V[0].getOuvert())
    {
        a->V[0].fermer();
        if(!a->R[0].getRempli() && a->R[1].getRempli() && a->nbReservoirVidange() != 3 ){
           a->R[0].setRempli(true);
           if(a->R[0].getPompe1().getEtat() == 1){
               a->moteur[0][0] = 1;
               if(a->moteur[1][0] == 1){
                   modifP22();
                   modifP22();
               }
               if(a->moteur[2][0]){
                   modifP32();
                   modifP32();
               }
           }
           if(a->R[0].getPompe2().getEtat() == 1){
               modifP12();
               modifP12();
           }
        }
        else if(!a->R[1].getRempli() && a->R[0].getRempli() && !a->R[0].getVidange()){
            a->R[1].setRempli(true);
            if(a->R[1].getPompe1().getEtat() == 1){
                a->moteur[1][1] = 1;
                if(a->moteur[0][1] == 1){
                    modifP12();
                    modifP12();
                }
                if(a->moteur[2][1]){
                    modifP32();
                    modifP32();
                }
            }
            if(a->R[1].getPompe2().getEtat() == 1){
                modifP22();
                modifP22();
            }
            if(!a->V[1].getOuvert() && !a->R[2].getRempli()){
                a->R[2].setRempli(true);
                if(a->R[2].getPompe1().getEtat() == 1){
                    a->moteur[2][2] = 1;
                    if(a->moteur[0][2] == 1){
                        modifP12();
                        modifP12();
                    }
                    if(a->moteur[1][2]){
                        modifP22();
                        modifP22();
                    }
                }
                if(a->R[2].getPompe2().getEtat() == 1){
                    modifP32();
                    modifP32();
                }
            }
        }

    }
    else
    {
        a->V[0].ouvrir();
        if(a->R[0].getVidange())
            f1->vidangeR1();
        if(a->R[1].getVidange())
            f1->vidangeR2();
    }
    updateFenetre();
    if(!a->actionNecessaire() && (int)f1->getChrono() != 0)
    {
        time_t tmp;
        time(&tmp);
        if((int)(tmp - f1->getChrono()) > 2)
            f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        else
            f1->decrementerNombreDeChrono();
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0 && a->actionNecessaire())
        f1->demarrerChrono();
}

void fenetrePilote::modifVT23()
{
    if(a->V[1].getOuvert())
    {
        a->V[1].fermer();
        if(!a->R[2].getRempli() && a->R[1].getRempli() && a->nbReservoirVidange() != 3 ){
           a->R[2].setRempli(true);
           if(a->R[2].getPompe1().getEtat() == 1){
               a->moteur[2][2] = 1;
               if(a->moteur[1][2] == 1){
                   modifP22();
                   modifP22();
               }
               if(a->moteur[0][2]){
                   modifP12();
                   modifP12();
               }
           }
           if(a->R[2].getPompe2().getEtat() == 1){
               modifP32();
               modifP32();
           }
        }
        else if(!a->R[1].getRempli() && a->R[2].getRempli() && !a->R[2].getVidange()){
            a->R[1].setRempli(true);
            if(a->R[1].getPompe1().getEtat() == 1){
                a->moteur[1][1] = 1;
                if(a->moteur[0][1] == 1){
                    modifP12();
                    modifP12();
                }
                if(a->moteur[2][1]){
                    modifP32();
                    modifP32();
                }
            }
            if(a->R[1].getPompe2().getEtat() == 1){
                modifP22();
                modifP22();
            }
            if(!a->V[0].getOuvert() && !a->R[0].getRempli()){
                a->R[0].setRempli(true);
                if(a->R[0].getPompe1().getEtat() == 1){
                    a->moteur[0][0] = 1;
                    if(a->moteur[1][0] == 1){
                        modifP22();
                        modifP22();
                    }
                    if(a->moteur[2][0]){
                        modifP32();
                        modifP32();
                    }
                }
                if(a->R[0].getPompe2().getEtat() == 1){
                    modifP12();
                    modifP12();
                }
            }
        }
    }else{
        a->V[1].ouvrir();
        if(a->R[2].getVidange())
            f1->vidangeR3();
        if(a->R[1].getVidange())
            f1->vidangeR2();
    }
    updateFenetre();
    if(!a->actionNecessaire() && (int)f1->getChrono() != 0)
    {
        time_t tmp;
        time(&tmp);
        if((int)(tmp - f1->getChrono()) > 2)
            f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        else
            f1->decrementerNombreDeChrono();
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0 && a->actionNecessaire())
        f1->demarrerChrono();
}

void fenetrePilote::modifV12()
{
    if(a->V[2].getOuvert())
    {
        a->V[2].fermer();
        if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getPompe1().getEtat() == 1 && a->moteur[0][2] != 1 && a->moteur[1][1] != 1 && a->moteur[2][1] != 1 && a->R[0].getRempli())
            a->moteur[0][1] = 1;
        if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getPompe1().getEtat() == 1 && a->moteur[1][2] != 1 && a->moteur[0][0] != 1 && a->moteur[2][0] != 1 && a->R[1].getRempli())
            a->moteur[1][0] = 1;
    }else{
        a->V[2].ouvrir();
        if(a->moteur[0][1] == 1)
        {
            a->moteur[0][1] = 0;
            if(!a->V[3].getOuvert() && a->moteur[2][2] != 1 && a->moteur[1][2] != 1)
                a->moteur[0][2] = 1;
        }
        if(a->moteur[1][0] == 1)
        {
            a->moteur[1][0] = 0;
            if(!a->V[4].getOuvert() && a->moteur[2][2] != 1 && a->moteur[0][2] != 1)
                a->moteur[1][2] = 1;
        }
    }
    updateFenetre();
    if(!a->actionNecessaire() && (int)f1->getChrono() != 0)
    {
        time_t tmp;
        time(&tmp);
        if((int)(tmp - f1->getChrono()) > 2)
            f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        else
            f1->decrementerNombreDeChrono();
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0 && a->actionNecessaire())
        f1->demarrerChrono();
}

void fenetrePilote::modifV13()
{
    if(a->V[3].getOuvert())
    {
        a->V[3].fermer();
        if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getPompe1().getEtat() == 1 && a->moteur[0][1] != 1 && a->moteur[1][2] != 1 && a->moteur[2][2] != 1 && a->R[0].getRempli())
            a->moteur[0][2] = 1;
        if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getPompe1().getEtat() == 1 && a->moteur[2][1] != 1 && a->moteur[1][0] != 1 && a->moteur[0][0] != 1 && a->R[2].getRempli())
            a->moteur[2][0] = 1;
    }else{
        a->V[3].ouvrir();
        if(a->moteur[0][2] == 1)
        {
            a->moteur[0][2] = 0;
            if(!a->V[2].getOuvert() && a->moteur[1][1] != 1 && a->moteur[2][1] != 1)
                a->moteur[0][1] = 1;
        }
        if(a->moteur[2][0] == 1)
        {
            a->moteur[2][0] = 0;
            if(!a->V[4].getOuvert() && a->moteur[1][1] != 1 && a->moteur[0][1] != 1)
                a->moteur[2][1] = 1;
        }
    }
    updateFenetre();
    if(!a->actionNecessaire() && (int)f1->getChrono() != 0)
    {
        time_t tmp;
        time(&tmp);
        if((int)(tmp - f1->getChrono()) > 2)
            f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        else
            f1->decrementerNombreDeChrono();
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0 && a->actionNecessaire())
        f1->demarrerChrono();
}

void fenetrePilote::modifV23()
{
    if(a->V[4].getOuvert())
    {
        a->V[4].fermer();
        if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getPompe1().getEtat() == 1 && a->moteur[1][0] != 1 && a->moteur[0][2] != 1 && a->moteur[2][2] != 1 && a->R[1].getRempli())
            a->moteur[1][2] = 1;
        if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getPompe1().getEtat() == 1 && a->moteur[2][0] != 1 && a->moteur[1][1] != 1 && a->moteur[0][1] != 1 && a->R[2].getRempli())
            a->moteur[2][1] = 1;
    }else{
        a->V[4].ouvrir();
        if(a->moteur[1][2] == 1)
        {
            a->moteur[1][2] = 0;
            if(!a->V[2].getOuvert() && a->moteur[0][0] != 1 && a->moteur[2][0] != 1)
                a->moteur[1][0] = 1;
        }
        if(a->moteur[2][1] == 1)
        {
            a->moteur[2][1] = 0;
            if(!a->V[3].getOuvert() && a->moteur[1][0] != 1 && a->moteur[0][0] != 1)
                a->moteur[2][0] = 1;
        }
    }
    updateFenetre();
    if(!a->actionNecessaire() && (int)f1->getChrono() != 0)
    {
        time_t tmp;
        time(&tmp);
        if((int)(tmp - f1->getChrono()) > 2)
            f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        else
            f1->decrementerNombreDeChrono();
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0 && a->actionNecessaire())
        f1->demarrerChrono();
}

void fenetrePilote::modifP12()
{
    if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getRempli())
    {
          a->R[0].getPompe2().arret();
          if(a->R[0].getPompe1().getEtat() != 1)
          {
              a->moteur[0][0] = 0;
              if(a->R[1].getPompe2().getEtat() == 1 && !a->V[2].getOuvert() && a->moteur[1][2] != 1 && a->R[1].getPompe1().getEtat() == 1)
                  a->moteur[1][0] = 1;
              else if(a->R[2].getPompe2().getEtat() == 1 && !a->V[3].getOuvert() && a->moteur[2][1] != 1 && a->R[2].getPompe1().getEtat() == 1)
                  a->moteur[2][0] = 1;
          }else{
              if(a->moteur[0][1] == 1)
              {
                  a->moteur[0][1] = 0;
                  if(a->R[2].getPompe1().getEtat() == 1 && !a->V[4].getOuvert() && a->R[2].getPompe2().getEtat() == 1)
                      a->moteur[2][1] = 1;
              }
              if(a->moteur[0][2] == 1)
              {
                  a->moteur[0][2] = 0;
                  if(a->R[1].getPompe1().getEtat() == 1 && !a->V[4].getOuvert() && a->R[1].getPompe2().getEtat() == 1)
                      a->moteur[1][2] = 1;
              }
          }
    }else if(a->R[0].getPompe2().getEtat() == -1){
        cout << "Cette pompe est en panne, vous ne pouvez donc effectuer aucune action."<< endl;
    }else if(a->R[0].getPompe2().getEtat() == 0 && a->R[0].getRempli()){
        a->R[0].getPompe2().marche();
        if(a->R[0].getPompe1().getEtat() != 1)
        {
            a->moteur[0][0] = 1;
            if(a->moteur[1][0] == 1)
            {
                a->moteur[1][0] = 0;
                if(a->moteur[2][2] == 0 && !a->V[4].getOuvert())
                    a->moteur[1][2] = 1;
            }
            if(a->moteur[2][0] == 1)
            {
                a->moteur[2][0] = 0;
                if(a->moteur[1][1] == 0 && !a->V[4].getOuvert())
                    a->moteur[2][1] = 1;
            }
        }else if(!a->V[2].getOuvert() && a->moteur[1][1] != 1 && a->moteur[2][1] != 1)
            a->moteur[0][1] = 1;
        else if(!a->V[3].getOuvert() && a->moteur[1][2] != 1 && a->moteur[2][2] != 1)
            a->moteur[0][2] = 1;
    }else if(a->R[0].getPompe2().getEtat() == 0 && !a->R[0].getRempli()){
        a->R[0].getPompe2().marche();
    }else if(a->R[0].getPompe2().getEtat() == 1 && !a->R[0].getRempli()){
        a->R[0].getPompe2().arret();
    }
    updateFenetre();
    if(!a->actionNecessaire() && (int)f1->getChrono() != 0)
    {
        time_t tmp;
        time(&tmp);
        if((int)(tmp - f1->getChrono()) > 2)
            f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        else
            f1->decrementerNombreDeChrono();
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0 && a->actionNecessaire())
        f1->demarrerChrono();
}

void fenetrePilote::modifP22()
{
    if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getRempli())
    {
        a->R[1].getPompe2().arret();
        if(a->R[1].getPompe1().getEtat() != 1)
        {
            a->moteur[1][1] = 0;
            if(a->R[0].getPompe2().getEtat() == 1 && !a->V[2].getOuvert() && a->moteur[0][2] != 1 && a->R[0].getPompe1().getEtat() == 1)
                a->moteur[0][1] = 1;
            else if(a->R[2].getPompe2().getEtat() == 1 && !a->V[4].getOuvert() && a->moteur[2][0] != 1 && a->R[2].getPompe1().getEtat() == 1)
                a->moteur[2][1] = 1;
        }else{
            if(a->moteur[1][0] == 1)
            {
                a->moteur[1][0] = 0;
                if(a->R[2].getPompe1().getEtat() == 1 && !a->V[3].getOuvert() && a->R[2].getPompe2().getEtat() == 1)
                    a->moteur[2][0] = 1;
            }
            if(a->moteur[1][2] == 1)
            {
                a->moteur[1][2] = 0;
                if(a->R[0].getPompe1().getEtat() == 1 && !a->V[3].getOuvert() && a->R[0].getPompe2().getEtat() == 1)
                    a->moteur[0][2] = 1;
            }
        }
    }else if(a->R[1].getPompe2().getEtat() == -1){
        cout << "Cette pompe est en panne, vous ne pouvez donc effectuer aucune action."<< endl;
    }else if(a->R[1].getPompe2().getEtat() == 0 && a->R[1].getRempli()){
        a->R[1].getPompe2().marche();
        if(a->R[1].getPompe1().getEtat() != 1)
        {
            a->moteur[1][1] = 1;
            if(a->moteur[0][1] == 1)
            {
                a->moteur[0][1] = 0;
                if(a->moteur[2][2] == 0 && !a->V[3].getOuvert())
                    a->moteur[0][2] = 1;
            }
            if(a->moteur[2][1] == 1)
            {
                a->moteur[2][1] = 0;
                if(a->moteur[0][0] == 0 && !a->V[3].getOuvert())
                    a->moteur[2][0] = 1;
            }
        }
        else if(!a->V[2].getOuvert() && a->moteur[0][0] != 1 && a->moteur[2][0] != 1)
            a->moteur[1][0] = 1;
        else if(!a->V[4].getOuvert() && a->moteur[0][2] != 1 && a->moteur[2][2] != 1)
            a->moteur[1][2] = 1;
    }else if(a->R[1].getPompe2().getEtat() == 0 && !a->R[1].getRempli()){
        a->R[1].getPompe2().marche();
    }else if(a->R[1].getPompe2().getEtat() == 1 && !a->R[1].getRempli()){
        a->R[1].getPompe2().arret();
    }
    updateFenetre();
    if(!a->actionNecessaire() && (int)f1->getChrono() != 0)
    {
        time_t tmp;
        time(&tmp);
        if((int)(tmp - f1->getChrono()) > 2)
            f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        else
            f1->decrementerNombreDeChrono();
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0 && a->actionNecessaire())
        f1->demarrerChrono();
}

void fenetrePilote::modifP32()
{
    if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getRempli())
    {
        a->R[2].getPompe2().arret();
        if(a->R[2].getPompe1().getEtat() != 1)
        {
            a->moteur[2][2] = 0;
            if(a->R[0].getPompe2().getEtat() == 1 && !a->V[3].getOuvert() && a->moteur[0][1] != 1 && a->R[0].getPompe1().getEtat() == 1)
                a->moteur[0][2] = 1;
            else if(a->R[1].getPompe2().getEtat() == 1 && !a->V[4].getOuvert() && a->moteur[1][0] != 1 && a->R[1].getPompe1().getEtat() == 1)
                a->moteur[1][2] = 1;
        }else{
            if(a->moteur[2][0] == 1)
            {
                a->moteur[2][0] = 0;
                if(a->R[1].getPompe1().getEtat() == 1 && !a->V[2].getOuvert() && a->R[1].getPompe2().getEtat() == 1)
                    a->moteur[1][0] = 1;
            }
            if(a->moteur[2][1] == 1)
            {
                a->moteur[2][1] = 0;
                if(a->R[0].getPompe1().getEtat() == 1 && !a->V[2].getOuvert() && a->R[0].getPompe2().getEtat() == 1)
                    a->moteur[0][1] = 1;
            }
        }
    }else if(a->R[2].getPompe2().getEtat() == -1){
        cout << "Cette pompe est en panne, vous ne pouvez donc effectuer aucune action."<< endl;
    }else if(a->R[2].getPompe2().getEtat() == 0 && a->R[2].getRempli()){
        a->R[2].getPompe2().marche();
        if(a->R[2].getPompe1().getEtat() != 1)
        {
            a->moteur[2][2] = 1;
            if(a->moteur[0][2] == 1)
            {
                a->moteur[0][2] = 0;
                if(a->moteur[1][1] == 0 && !a->V[2].getOuvert())
                    a->moteur[0][1] = 1;
            }
            if(a->moteur[1][2] == 1)
            {
                a->moteur[1][2] = 0;
                if(a->moteur[0][0] == 0 && !a->V[2].getOuvert())
                    a->moteur[1][0] = 1;
            }
        }
        else if(!a->V[3].getOuvert() && a->moteur[0][0] != 1 && a->moteur[1][0] != 1)
            a->moteur[2][0] = 1;
        else if(!a->V[4].getOuvert() && a->moteur[0][1] != 1 && a->moteur[1][1] != 1)
            a->moteur[2][1] = 1;
    }else if(a->R[2].getPompe2().getEtat() == 0 && !a->R[2].getRempli()){
        a->R[2].getPompe2().marche();
    }else if(a->R[2].getPompe2().getEtat() == 1 && !a->R[2].getRempli()){
        a->R[2].getPompe2().arret();
    }
    updateFenetre();
    if(!a->actionNecessaire() && (int)f1->getChrono() != 0)
    {
        time_t tmp;
        time(&tmp);
        if((int)(tmp - f1->getChrono()) > 2)
            f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        else
            f1->decrementerNombreDeChrono();
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0 && a->actionNecessaire())
        f1->demarrerChrono();
}
