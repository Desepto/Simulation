#include "fenetrepilote.h"
#include "ui_fenetrepilote.h"

fenetrePilote::fenetrePilote(Avion* a,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fenetrePilote)
{
    ui->setupUi(this);
    this->a = a;

    connect(ui->V12, SIGNAL(clicked()), this, SLOT(modifV12()));
    connect(ui->V23, SIGNAL(clicked()), this, SLOT(modifV23()));
    connect(ui->V21, SIGNAL(clicked()), this, SLOT(modifV21()));
    connect(ui->V31, SIGNAL(clicked()), this, SLOT(modifV31()));
    connect(ui->V32, SIGNAL(clicked()), this, SLOT(modifV32()));
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

void fenetrePilote::updateFenetre() // A tester
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

void fenetrePilote::modifV12()
{
}

void fenetrePilote::modifV23()
{
}

void fenetrePilote::modifV21()
{
}

void fenetrePilote::modifV31()
{
}

void fenetrePilote::modifV32()
{
}

void fenetrePilote::modifP12()
{
}

void fenetrePilote::modifP22()
{
}

void fenetrePilote::modifP32()
{
}
