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
}

fenetrePilote::~fenetrePilote()
{
    delete ui;
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
