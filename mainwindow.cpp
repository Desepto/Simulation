#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Avion* a,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}
