#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Avion* a,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->a = a;

    connect(ui->P11, SIGNAL(clicked()), this, SLOT(panneP11()));
    connect(ui->P12, SIGNAL(clicked()), this, SLOT(panneP12()));
    connect(ui->P21, SIGNAL(clicked()), this, SLOT(panneP21()));
    connect(ui->P22, SIGNAL(clicked()), this, SLOT(panneP22()));
    connect(ui->P31, SIGNAL(clicked()), this, SLOT(panneP31()));
    connect(ui->P32, SIGNAL(clicked()), this, SLOT(panneP32()));
    connect(ui->R1, SIGNAL(clicked()), this, SLOT(vidanceR1()));
    connect(ui->R2, SIGNAL(clicked()), this, SLOT(vidanceR1()));
    connect(ui->R3, SIGNAL(clicked()), this, SLOT(vidanceR1()));

}



MainWindow::~MainWindow()
{
    delete ui;
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




