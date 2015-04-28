#include "aide.h"
#include "ui_aide.h"

Aide::Aide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Aide)
{
    ui->setupUi(this);
}

Aide::~Aide()
{
    delete ui;
}

void Aide::on_pushButton_clicked()
{
    this->close();
}
