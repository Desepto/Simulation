#include "affichertexte.h"
#include "ui_affichertexte.h"

afficherTexte::afficherTexte(int aAfficher, QSqlDatabase BDD, QString nom, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::afficherTexte)
{
    ui->setupUi(this);
    if(aAfficher == 1) // si on veut afficher l'aide
    {
        this->setWindowTitle("Aide");
        this->ui->texte->setText("Ceci est l'aide ! \n");
    }
    if(aAfficher == 2)
    {
        this->setWindowTitle("Scores");
        QString aEcrire = "Dix derniers scores pour : ", usrId;
        aEcrire += nom + "\n";
        QSqlQuery rqt;
        if(rqt.exec("SELECT UsrId FROM User Where Nom='" + nom + "'"))
        {
            rqt.next();
            usrId.setNum(rqt.value(0).toInt(), 10);
        }

        rqt.exec("SELECT Score FROM Score WHERE IdUser='"+ usrId +"'");
        int i = 0;
        while(rqt.next() && i < 10)
        {
            aEcrire += QString::number(i) + ") ";
            aEcrire += QString::number(rqt.value(0).toInt());
            aEcrire += "\n\n";
            i++;
        }
    this->ui->texte->setText(aEcrire);
    }

}

afficherTexte::~afficherTexte()
{
    delete ui;
}

void afficherTexte::on_pushButton_clicked()
{
    this->close();
}
