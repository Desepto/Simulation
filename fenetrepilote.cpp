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
    connect(ui->V32, SIGNAL(clicked()), this, SLOT(modifP32()));

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
        this->f1->updateFenetre(false);

}

void fenetrePilote::addfenetre(MainWindow *f1)
{
    this->f1 = f1;
}

void fenetrePilote::closeEvent(QCloseEvent *)
{
    int score = f1->getTempsTotalEcoule()/f1->getNombreDeChrono();
    if(score <= 3)
        cout << "Bravo, votre score est de 10/10!" << endl;
    else{
        switch (score) {
            case 4:
                cout << "Votre score est de 9/10!" << endl;
                break;

            case 5:
                cout << "Votre score est de 8/10!" << endl;
                break;

            case 6:
                cout << "Votre score est de 7/10!" << endl;
                break;

            case 7:
                cout << "Votre score est de 6/10!" << endl;
                break;

            case 8:
                cout << "Votre score est de 5/10!" << endl;
                break;

            case 9:
                cout << "Votre score est de 4/10!" << endl;
                break;

            case 10:
                cout << "Votre score est de 3/10!" << endl;
                break;

            case 11:
                cout << "Votre score est de 2/10!" << endl;
                break;

            case 12:
                cout << "Votre score est de 1/10!" << endl;
                break;

            default:
                cout << "Votre score est de 0/10!" << endl;
                break;
        }
    }
    this->f1->close();
    this->close();
}

void fenetrePilote::modifVT12()
{
    if(a->getVanne(0).getOuvert())
    {
        a->getVanne(0).fermer();
        if(!a->getReservoir(0).getRempli() && a->getReservoir(1).getRempli() && a->nbReservoirVidange() != 3 )
           a->getReservoir(0).setRempli(true);
        else if(!a->getReservoir(1).getRempli() && a->getReservoir(0).getRempli() && !a->getReservoir(0).getVidange())
            a->getReservoir(1).setRempli(true);

    }else{
        a->getVanne(0).ouvrir();
        if(a->getReservoir(0).getVidange())
            f1->vidangeR1();
        if(a->getReservoir(1).getVidange())
            f1->vidangeR2();
    }
    updateFenetre();
    if(!a->actionNecessaire())
    {
        time_t tmp;
        time(&tmp);
        f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0)
        f1->demarrerChrono();
}

void fenetrePilote::modifVT23()
{
    if(a->getVanne(1).getOuvert())
    {
        a->getVanne(1).fermer();
        if(!a->getReservoir(2).getRempli() && a->getReservoir(1).getRempli() && a->nbReservoirVidange() != 3 )
           a->getReservoir(2).setRempli(true);
        else if(!a->getReservoir(1).getRempli() && a->getReservoir(2).getRempli() && !a->getReservoir(2).getVidange())
            a->getReservoir(1).setRempli(true);
    }else{
        a->getVanne(1).ouvrir();
        if(a->getReservoir(2).getVidange())
            f1->vidangeR3();
        if(a->getReservoir(1).getVidange())
            f1->vidangeR2();
    }
    updateFenetre();
    if(!a->actionNecessaire())
    {
        time_t tmp;
        time(&tmp);
        f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0)
        f1->demarrerChrono();
}

void fenetrePilote::modifV12()
{
    if(a->getVanne(2).getOuvert())
    {
        a->getVanne(2).fermer();
        if(a->getReservoir(0).getPompe2().getEtat() == 1 && a->getReservoir(0).getPompe1().getEtat() == 1 && a->getMoteur(0,2) != 1 && a->getMoteur(1,1) != 1 && a->getMoteur(2,1) != 1 && a->getReservoir(0).getRempli())
            a->setMoteur(0,1,1);
        if(a->getReservoir(1).getPompe2().getEtat() == 1 && a->getReservoir(1).getPompe1().getEtat() == 1 && a->getMoteur(1,2) != 1 && a->getMoteur(0,0) != 1 && a->getMoteur(2,0) != 1 && a->getReservoir(1).getRempli())
            a->setMoteur(1,0,1);
    }else{
        a->getVanne(2).ouvrir();
        if(a->getMoteur(0,1) == 1)
        {
            a->setMoteur(0,1,0);
            if(!a->getVanne(3).getOuvert() && a->getMoteur(2,2) != 1 && a->getMoteur(1,2) != 1)
                a->setMoteur(0,2,1);
        }
        if(a->getMoteur(1,0) == 1)
        {
            a->setMoteur(1,0,0);
            if(!a->getVanne(4).getOuvert() && a->getMoteur(2,2) != 1 && a->getMoteur(0,2) != 1)
                a->setMoteur(1,2,1);
        }
    }
    updateFenetre();
    if(!a->actionNecessaire())
    {
        time_t tmp;
        time(&tmp);
        f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0)
        f1->demarrerChrono();
}

void fenetrePilote::modifV13()
{
    if(a->getVanne(3).getOuvert())
    {
        a->getVanne(3).fermer();
        if(a->getReservoir(0).getPompe2().getEtat() == 1 && a->getReservoir(0).getPompe1().getEtat() == 1 && a->getMoteur(0,1) != 1 && a->getMoteur(1,2) != 1 && a->getMoteur(2,2) != 1 && a->getReservoir(0).getRempli())
            a->setMoteur(0,2,1);
        if(a->getReservoir(2).getPompe2().getEtat() == 1 && a->getReservoir(2).getPompe1().getEtat() == 1 && a->getMoteur(2,1) != 1 && a->getMoteur(1,0) != 1 && a->getMoteur(0,0) != 1 && a->getReservoir(2).getRempli())
            a->setMoteur(2,0,1);
    }else{
        a->getVanne(3).ouvrir();
        if(a->getMoteur(0,2) == 1)
        {
            a->setMoteur(0,2,0);
            if(!a->getVanne(2).getOuvert() && a->getMoteur(1,1) != 1 && a->getMoteur(2,1) != 1)
                a->setMoteur(0,1,1);
        }
        if(a->getMoteur(2,0) == 1)
        {
            a->setMoteur(2,0,0);
            if(!a->getVanne(4).getOuvert() && a->getMoteur(1,1) != 1 && a->getMoteur(0,1) != 1)
                a->setMoteur(2,1,1);
        }
    }
    updateFenetre();
    if(!a->actionNecessaire())
    {
        time_t tmp;
        time(&tmp);
        f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0)
        f1->demarrerChrono();
}

void fenetrePilote::modifV23()
{
    if(a->getVanne(4).getOuvert())
    {
        a->getVanne(4).fermer();
        if(a->getReservoir(1).getPompe2().getEtat() == 1 && a->getReservoir(1).getPompe1().getEtat() == 1 && a->getMoteur(1,0) != 1 && a->getMoteur(0,2) != 1 && a->getMoteur(2,2) != 1 && a->getReservoir(1).getRempli())
            a->setMoteur(1,2,1);
        if(a->getReservoir(2).getPompe2().getEtat() == 1 && a->getReservoir(2).getPompe1().getEtat() == 1 && a->getMoteur(2,0) != 1 && a->getMoteur(1,1) != 1 && a->getMoteur(0,1) != 1 && a->getReservoir(2).getRempli())
            a->setMoteur(2,1,1);
    }else{
        a->getVanne(4).ouvrir();
        if(a->getMoteur(1,2) == 1)
        {
            a->setMoteur(1,2,0);
            if(!a->getVanne(2).getOuvert() && a->getMoteur(0,0) != 1 && a->getMoteur(2,0) != 1)
                a->setMoteur(1,0,1);
        }
        if(a->getMoteur(2,1) == 1)
        {
            a->setMoteur(2,1,0);
            if(!a->getVanne(3).getOuvert() && a->getMoteur(1,0) != 1 && a->getMoteur(0,0) != 1)
                a->setMoteur(2,0,1);
        }
    }
    updateFenetre();
    if(!a->actionNecessaire())
    {
        time_t tmp;
        time(&tmp);
        f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0)
        f1->demarrerChrono();
}

void fenetrePilote::modifP12()
{
    if(a->getReservoir(0).getPompe2().getEtat() == 1 && a->getReservoir(0).getRempli())
    {
          a->getReservoir(0).getPompe2().arret();
          if(a->getReservoir(0).getPompe1().getEtat() != 1)
          {
              a->setMoteur(0,0,0);
              if(a->getReservoir(1).getPompe2().getEtat() == 1 && !a->getVanne(2).getOuvert() && a->getMoteur(1,2) != 1 && a->getReservoir(1).getPompe1().getEtat() == 1)
                  a->setMoteur(1,0,1);
              else if(a->getReservoir(2).getPompe2().getEtat() == 1 && !a->getVanne(3).getOuvert() && a->getMoteur(2,1) != 1 && a->getReservoir(2).getPompe1().getEtat() == 1)
                  a->setMoteur(2,0,1);
          }else{
              if(a->getMoteur(0,1) == 1)
              {
                  a->setMoteur(0,1,0);
                  if(a->getReservoir(2).getPompe1().getEtat() == 1 && !a->getVanne(4).getOuvert() && a->getReservoir(2).getPompe2().getEtat() == 1)
                      a->setMoteur(2,1,1);
              }
              if(a->getMoteur(0,2) == 1)
              {
                  a->setMoteur(0,2,0);
                  if(a->getReservoir(1).getPompe1().getEtat() == 1 && !a->getVanne(4).getOuvert() && a->getReservoir(1).getPompe2().getEtat() == 1)
                      a->setMoteur(1,2,1);
              }
          }
    }else if(a->getReservoir(0).getPompe2().getEtat() == -1){
        cout << "Cette pompe est en panne, vous ne pouvez donc effectuer aucune action."<< endl;
    }else if(a->getReservoir(0).getPompe2().getEtat() == 0 && a->getReservoir(0).getRempli()){
        a->getReservoir(0).getPompe2().marche();
        if(a->getReservoir(0).getPompe1().getEtat() != 1)
        {
            a->setMoteur(0,0,1);
            if(a->getMoteur(1,0) == 1)
            {
                a->setMoteur(1,0,0);
                if(a->getMoteur(2,2) == 0 && !a->getVanne(4).getOuvert())
                    a->setMoteur(1,2,1);
            }
            if(a->getMoteur(2,0) == 1)
            {
                a->setMoteur(2,0,0);
                if(a->getMoteur(1,1) == 0 && !a->getVanne(4).getOuvert())
                    a->setMoteur(2,1,1);
            }
        }else if(!a->getVanne(2).getOuvert() && a->getMoteur(1,1) != 1 && a->getMoteur(2,1) != 1)
            a->setMoteur(0,1,1);
        else if(!a->getVanne(3).getOuvert() && a->getMoteur(1,2) != 1 && a->getMoteur(2,2) != 1)
            a->setMoteur(0,2,1);
    }else if(a->getReservoir(0).getPompe2().getEtat() == 0 && !a->getReservoir(0).getRempli()){
        a->getReservoir(0).getPompe2().marche();
    }else if(a->getReservoir(0).getPompe2().getEtat() == 1 && !a->getReservoir(0).getRempli()){
        a->getReservoir(0).getPompe2().arret();
    }
    updateFenetre();
    if(!a->actionNecessaire())
    {
        time_t tmp;
        time(&tmp);
        f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0)
        f1->demarrerChrono();
}

void fenetrePilote::modifP22()
{
    if(a->getReservoir(1).getPompe2().getEtat() == 1 && a->getReservoir(1).getRempli())
    {
        a->getReservoir(1).getPompe2().arret();
        if(a->getReservoir(1).getPompe1().getEtat() != 1)
        {
            a->setMoteur(1,1,0);
            if(a->getReservoir(0).getPompe2().getEtat() == 1 && !a->getVanne(2).getOuvert() && a->getMoteur(0,2) != 1 && a->getReservoir(0).getPompe1().getEtat() == 1)
                a->setMoteur(0,1,1);
            else if(a->getReservoir(2).getPompe2().getEtat() == 1 && !a->getVanne(4).getOuvert() && a->getMoteur(2,0) != 1 && a->getReservoir(2).getPompe1().getEtat() == 1)
                a->setMoteur(2,1,1);
        }else{
            if(a->getMoteur(1,0) == 1)
            {
                a->setMoteur(1,0,0);
                if(a->getReservoir(2).getPompe1().getEtat() == 1 && !a->getVanne(3).getOuvert() && a->getReservoir(2).getPompe2().getEtat() == 1)
                    a->setMoteur(2,0,1);
            }
            if(a->getMoteur(1,2) == 1)
            {
                a->setMoteur(1,2,0);
                if(a->getReservoir(0).getPompe1().getEtat() == 1 && !a->getVanne(3).getOuvert() && a->getReservoir(0).getPompe2().getEtat() == 1)
                    a->setMoteur(0,2,1);
            }
        }
    }else if(a->getReservoir(1).getPompe2().getEtat() == -1){
        cout << "Cette pompe est en panne, vous ne pouvez donc effectuer aucune action."<< endl;
    }else if(a->getReservoir(1).getPompe2().getEtat() == 0 && a->getReservoir(1).getRempli()){
        a->getReservoir(1).getPompe2().marche();
        if(a->getReservoir(1).getPompe1().getEtat() != 1)
        {
            a->setMoteur(1,1,1);
            if(a->getMoteur(0,1) == 1)
            {
                a->setMoteur(0,1,0);
                if(a->getMoteur(2,2) == 0 && !a->getVanne(3).getOuvert())
                    a->setMoteur(0,2,1);
            }
            if(a->getMoteur(2,1) == 1)
            {
                a->setMoteur(2,1,0);
                if(a->getMoteur(0,0) == 0 && !a->getVanne(3).getOuvert())
                    a->setMoteur(2,0,1);
            }
        }
        else if(!a->getVanne(2).getOuvert() && a->getMoteur(0,0) != 1 && a->getMoteur(2,0) != 1)
            a->setMoteur(1,0,1);
        else if(!a->getVanne(4).getOuvert() && a->getMoteur(0,2) != 1 && a->getMoteur(2,2) != 1)
            a->setMoteur(1,2,1);
    }else if(a->getReservoir(1).getPompe2().getEtat() == 0 && !a->getReservoir(1).getRempli()){
        a->getReservoir(1).getPompe2().marche();
    }else if(a->getReservoir(1).getPompe2().getEtat() == 1 && !a->getReservoir(1).getRempli()){
        a->getReservoir(1).getPompe2().arret();
    }
    updateFenetre();
    if(!a->actionNecessaire())
    {
        time_t tmp;
        time(&tmp);
        f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0)
        f1->demarrerChrono();
}

void fenetrePilote::modifP32()
{
    if(a->getReservoir(2).getPompe2().getEtat() == 1 && a->getReservoir(2).getRempli())
    {
        a->getReservoir(2).getPompe2().arret();
        if(a->getReservoir(2).getPompe1().getEtat() != 1)
        {
            a->setMoteur(2,2,0);
            if(a->getReservoir(0).getPompe2().getEtat() == 1 && !a->getVanne(3).getOuvert() && a->getMoteur(0,1) != 1 && a->getReservoir(0).getPompe1().getEtat() == 1)
                a->setMoteur(0,2,1);
            else if(a->getReservoir(1).getPompe2().getEtat() == 1 && !a->getVanne(4).getOuvert() && a->getMoteur(1,0) != 1 && a->getReservoir(1).getPompe1().getEtat() == 1)
                a->setMoteur(1,2,1);
        }else{
            if(a->getMoteur(2,0) == 1)
            {
                a->setMoteur(2,0,0);
                if(a->getReservoir(1).getPompe1().getEtat() == 1 && !a->getVanne(2).getOuvert() && a->getReservoir(1).getPompe2().getEtat() == 1)
                    a->setMoteur(1,0,1);
            }
            if(a->getMoteur(2,1) == 1)
            {
                a->setMoteur(2,1,0);
                if(a->getReservoir(0).getPompe1().getEtat() == 1 && !a->getVanne(2).getOuvert() && a->getReservoir(0).getPompe2().getEtat() == 1)
                    a->setMoteur(0,1,1);
            }
        }
    }else if(a->getReservoir(2).getPompe2().getEtat() == -1){
        cout << "Cette pompe est en panne, vous ne pouvez donc effectuer aucune action."<< endl;
    }else if(a->getReservoir(2).getPompe2().getEtat() == 0 && a->getReservoir(2).getRempli()){
        a->getReservoir(2).getPompe2().marche();
        if(a->getReservoir(2).getPompe1().getEtat() != 1)
        {
            a->setMoteur(2,2,1);
            if(a->getMoteur(0,2) == 1)
            {
                a->setMoteur(0,2,0);
                if(a->getMoteur(1,1) == 0 && !a->getVanne(2).getOuvert())
                    a->setMoteur(0,1,1);
            }
            if(a->getMoteur(1,2) == 1)
            {
                a->setMoteur(1,2,0);
                if(a->getMoteur(0,0) == 0 && !a->getVanne(2).getOuvert())
                    a->setMoteur(1,0,1);
            }
        }
        else if(!a->getVanne(3).getOuvert() && a->getMoteur(0,0) != 1 && a->getMoteur(1,0) != 1)
            a->setMoteur(2,0,1);
        else if(!a->getVanne(4).getOuvert() && a->getMoteur(0,1) != 1 && a->getMoteur(1,1) != 1)
            a->setMoteur(2,1,1);
    }else if(a->getReservoir(2).getPompe2().getEtat() == 0 && !a->getReservoir(2).getRempli()){
        a->getReservoir(2).getPompe2().marche();
    }else if(a->getReservoir(2).getPompe2().getEtat() == 1 && !a->getReservoir(2).getRempli()){
        a->getReservoir(2).getPompe2().arret();
    }
    updateFenetre();
    if(!a->actionNecessaire())
    {
        time_t tmp;
        time(&tmp);
        f1->setTempsTotalEcoule(f1->getTempsTotalEcoule() + (int) (tmp - f1->getChrono()));
        f1->setChrono(0);
    }else if( (int)f1->getChrono() == 0)
        f1->demarrerChrono();
}
