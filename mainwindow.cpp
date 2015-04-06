#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Avion* a, QString nom, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->a = a;
    this->nom = nom;

    connect(ui->P11, SIGNAL(clicked()), this, SLOT(panneP11()));
    connect(ui->P12, SIGNAL(clicked()), this, SLOT(panneP12()));
    connect(ui->P21, SIGNAL(clicked()), this, SLOT(panneP21()));
    connect(ui->P22, SIGNAL(clicked()), this, SLOT(panneP22()));
    connect(ui->P31, SIGNAL(clicked()), this, SLOT(panneP31()));
    connect(ui->P32, SIGNAL(clicked()), this, SLOT(panneP32()));
    connect(ui->R1, SIGNAL(clicked()), this, SLOT(vidangeR1()));
    connect(ui->R2, SIGNAL(clicked()), this, SLOT(vidangeR2()));
    connect(ui->R3, SIGNAL(clicked()), this, SLOT(vidangeR3()));

    this->move(0, 50);

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addfenetre(fenetrePilote *f1)
{
    this->f1 = f1;
}

void MainWindow::updateFenetre()
{
    updateReservoir();
    updatePompe();
    updateVanne();

}

void MainWindow::updateVanne()
{
    this->ui->V12->setPixmap(this->a->V[0].getpixmap());
    this->ui->V23->setPixmap(this->a->V[1].getpixmap());
    this->ui->V21->setPixmap(this->a->V[2].getpixmap());
    this->ui->V31->setPixmap(this->a->V[3].getpixmap());
    this->ui->V32->setPixmap(this->a->V[4].getpixmap());
}

void MainWindow::updatePompe()
{
    this->ui->P11->setEnabled(this->a->R[1].getPompe1().getEtat());
    this->ui->P12->setEnabled(this->a->R[1].getPompe2().getEtat());

    this->ui->P21->setEnabled(this->a->R[2].getPompe1().getEtat());
    this->ui->P22->setEnabled(this->a->R[2].getPompe2().getEtat());

    this->ui->P31->setEnabled(this->a->R[2].getPompe1().getEtat());
    this->ui->P32->setEnabled(this->a->R[2].getPompe2().getEtat());
}

void MainWindow::updateReservoir()
{
    this->ui->R1->setEnabled(this->a->R[1].getRempli());
    this->ui->F1->setPalette(this->a->R[1].getCouleur());

    this->ui->R2->setEnabled(this->a->R[2].getRempli());
    this->ui->F2->setPalette(this->a->R[2].getCouleur());

    this->ui->R3->setEnabled(this->a->R[3].getRempli());
    this->ui->F3->setPalette(this->a->R[3].getCouleur());
}

void MainWindow::closeEvent(QCloseEvent *)
{
    this->f1->close();
    this->close();
}

void MainWindow::on_actionLancer_Simulation_triggered()
{
    this->ui->centralwidget->setEnabled(true);
}

void MainWindow::on_actionStopper_simulation_triggered()
{
    this->ui->centralwidget->setEnabled(false);
}

void MainWindow::on_actionR_initialiser_Simulation_triggered()
{
    this->a->reset();
    this->updateFenetre();
}

void MainWindow::panneP11()
{


}

void MainWindow::panneP12()
{
}

void MainWindow::panneP21()
{
}

void MainWindow::panneP22()
{
}

void MainWindow::panneP31()
{
}

void MainWindow::panneP32()
{
}

void MainWindow::vidangeR1()
{
}

void MainWindow::vidangeR2()
{
}

void MainWindow::vidangeR3()
{
}




