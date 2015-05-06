#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(Avion* a, QString nom, QSqlDatabase BDD, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->timer = new QTimer(this);
    ui->setupUi(this);
    this->a = a;
    this->nom = nom;
    this->chrono = 0;
    this->tempsTotalEcoule = 0;
    this->nombreDeChrono = 0;
    this->BDD = BDD;

    // Initialisation du choix aléatoire de panne
    //this->ordrePanneAlea = {0,1,2,3,4,5,6,7,8,0};
    for(int i = 0; i < 9; i++)
        this->ordrePanneAlea[i] = i;
    this->ordrePanneAlea[9] = 0;
    qsrand(time(NULL));
    int k,l, temp;

    for(int i = 0; i < 30; i++)
    {
        k = qrand() % 9;
        qDebug() << "k = " << k << endl;
        l = qrand() % 9;
        qDebug() << "l = " << l << endl;
        temp = ordrePanneAlea[k];
        ordrePanneAlea[k] = ordrePanneAlea[l];
        ordrePanneAlea[l] = temp;
    }
    for(int i = 0; i < 9; i++)
        qDebug() << "tab[" << i << "] =" << ordrePanneAlea[i] << endl;
    // Fin de l'init de choix aléatoire de panne

    connect(timer, SIGNAL(timeout()), this, SLOT(panneAlea()));

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

void MainWindow::updateFenetre(bool premierAppel) // A tester
{
    updateReservoir();
    updatePompe();
    updateVanne();
    updateMoteur(); // fais l'update du moteur et des diodes

    qDebug("Etat de l'avion :\n");
    qDebug("Reservoir 1 : rempli : %d / vidange : %d", this->a->R[0].getRempli(), this->a->R[0].getVidange());
    qDebug("Reservoir 2 : rempli : %d / vidange : %d", this->a->R[1].getRempli(), this->a->R[1].getVidange());
    qDebug("Reservoir 3 : rempli : %d / vidange : %d", this->a->R[2].getRempli(), this->a->R[2].getVidange());
    qDebug("Pompe 1.1 : %d / Pompe 1.2 : %d ", this->a->R[0].getPompe1().getEtat(), this->a->R[0].getPompe2().getEtat());
    qDebug("Pompe 2.1 : %d / Pompe 2.2 : %d ", this->a->R[1].getPompe1().getEtat(), this->a->R[1].getPompe2().getEtat());
    qDebug("Pompe 3.1 : %d / Pompe 3.2 : %d ", this->a->R[2].getPompe1().getEtat(), this->a->R[2].getPompe2().getEtat());
    qDebug("Vanne VT12 : %d", this->a->V[0].getOuvert());
    qDebug("Vanne VT23 : %d", this->a->V[1].getOuvert());
    qDebug("Vanne V12  : %d", this->a->V[2].getOuvert());
    qDebug("Vanne V23  : %d", this->a->V[3].getOuvert());
    qDebug("Vanne V31  : %d", this->a->V[4].getOuvert());

    qDebug();
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
            qDebug("Moteur[%d][%d] = %d", i, j, this->a->moteur[i][j]);
        qDebug("\n");
    }

    if(premierAppel)
        this->f1->updateFenetre(false);

}

void MainWindow::updateMoteur()
{

    this->ui->M11->setPixmap(this->a->getCouleurAlimMoteur(0,0));
    this->ui->M12->setPixmap(this->a->getCouleurAlimMoteur(1,0));
    this->ui->M13->setPixmap(this->a->getCouleurAlimMoteur(2,0));

    this->ui->M21->setPixmap(this->a->getCouleurAlimMoteur(0,1));
    this->ui->M22->setPixmap(this->a->getCouleurAlimMoteur(1,1));
    this->ui->M23->setPixmap(this->a->getCouleurAlimMoteur(2,1));

    this->ui->M31->setPixmap(this->a->getCouleurAlimMoteur(0,2));
    this->ui->M32->setPixmap(this->a->getCouleurAlimMoteur(1,2));
    this->ui->M33->setPixmap(this->a->getCouleurAlimMoteur(2,2));

    this->ui->F7->setPalette(this->a->isAlimente(0));
    this->ui->F8->setPalette(this->a->isAlimente(1));
    this->ui->F9->setPalette(this->a->isAlimente(2));

}

void MainWindow::updateVanne()
{
    this->ui->VT12->setPixmap(this->a->V[0].getpixmap());
    this->ui->VT23->setPixmap(this->a->V[1].getpixmap());
    this->ui->V12->setPixmap(this->a->V[2].getpixmap());
    this->ui->V13->setPixmap(this->a->V[3].getpixmap());
    this->ui->V23->setPixmap(this->a->V[4].getpixmap());
}

void MainWindow::updatePompe()
{
    printf("pompe2 = %d\n", this->a->R[0].getPompe2().getEnFonction());
    this->ui->P11->setEnabled(this->a->R[0].getPompe1().getEnFonction());
    this->ui->P12->setEnabled(this->a->R[0].getPompe2().getEnFonction());

    this->ui->P21->setEnabled(this->a->R[1].getPompe1().getEnFonction());
    this->ui->P22->setEnabled(this->a->R[1].getPompe2().getEnFonction());

    this->ui->P31->setEnabled(this->a->R[2].getPompe1().getEnFonction());
    this->ui->P32->setEnabled(this->a->R[2].getPompe2().getEnFonction());
}

void MainWindow::updateReservoir()
{
    this->ui->R1->setEnabled(this->a->R[0].getRempli());
    this->ui->F1->setPalette(this->a->R[0].getCouleur());

    this->ui->R2->setEnabled(this->a->R[1].getRempli());
    this->ui->F2->setPalette(this->a->R[1].getCouleur());

    this->ui->R3->setEnabled(this->a->R[2].getRempli());
    this->ui->F3->setPalette(this->a->R[2].getCouleur());
}

void MainWindow::finSimulation()
{
    qDebug()<< "debug";
    if(this->timer->isActive())
        timer->stop();
    saveScore();
}

void MainWindow::saveScore()
{
    if(this->getNombreDeChrono() < 2){
        cout << "nombre chrono " << getNombreDeChrono() << endl;
        QString str("Vous n'avez pas réparer de panne (ou pas assez), vous n'avez donc pas de score!");
        QMessageBox::information(this,"Score", str);
    }else if(a->actionNecessaire()){
        QString str("La simulation n'est pas finie, vous n'avez donc pas de score!");
        QMessageBox::information(this,"Score", str);
    }else{
        qDebug() << "Tps total écoulé" << this->getTempsTotalEcoule() << "nombre de chronos" << this->getNombreDeChrono() << endl;
        int score = 0;
        score = this->getTempsTotalEcoule()/this->getNombreDeChrono();
        int stock = 0;
        qDebug() << "Le score est à : " << score << endl;

        if(score <= 3)
        {
            QMessageBox::information(this,"Score", "Votre score est de 10/10 !");
            stock = 10;
        }
        else if (score < 13)
        {
            QString str("Votre score est de ");
            str += QString::number(13 - score) ;
            str += "/10 !";
            QMessageBox::information(this,"Score", str);
            stock = 13 - score;
        }
        else
        {
            QMessageBox::information(this,"Score", "Votre score est de 0/10 !");
            stock = 0;
        }

        QSqlQuery rqt;
        QString usrId;
        if(rqt.exec("SELECT UsrId FROM User Where Nom='" + this->nom + "'"))
        {
            rqt.next();
            usrId.setNum(rqt.value(0).toInt(), 10);

            qDebug() << usrId;
        }
        QString Sstock;
        Sstock.setNum(stock);
        rqt.exec("INSERT INTO Score (Score, IdUser) VALUES('"+ Sstock +"', '"+ usrId +"')");
    }
}

time_t MainWindow :: getChrono(){
    return chrono;
}

void MainWindow :: setChrono(int temps){
    chrono = temps;
}

void MainWindow :: demarrerChrono(){
    time(&chrono);
    nombreDeChrono++;
}

int MainWindow :: getTempsTotalEcoule(){
    return tempsTotalEcoule;
}

int MainWindow :: getNombreDeChrono(){
    return nombreDeChrono;
}

void MainWindow :: decrementerNombreDeChrono(){
    nombreDeChrono--;
}

void MainWindow :: setTempsTotalEcoule (int temps){
    tempsTotalEcoule = temps;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    this->f1->close();
    this->close();
    finSimulation();
}

void MainWindow::on_actionLancer_Simulation_triggered()
{
    this->ui->centralwidget->setEnabled(true);
    this->f1->centralWidget()->setEnabled(true);
}

void MainWindow::on_actionStopper_simulation_triggered()
{
    this->ui->centralwidget->setEnabled(false);
    this->f1->centralWidget()->setEnabled(false);
    this->timer->stop();
}

void MainWindow::on_actionR_initialiser_Simulation_triggered()
{
    finSimulation();
    this->a->reset();
    this->updateFenetre();
    this->chrono = 0;
    this->tempsTotalEcoule = 0;
    this->nombreDeChrono = 0;
}

void MainWindow::on_actionChanger_Utilisateur_triggered()
{
    finSimulation();
    Identification* fenetre = new Identification(this->a, this->BDD, this);
    fenetre->show();
}

void MainWindow::on_actionAfficher_Aide_triggered()
{
    afficherTexte* fenetre = new afficherTexte(1, this->BDD,this->nom, this);
    fenetre->show();
}

void MainWindow::on_actionSupprimer_historique_triggered()
{
    QSqlQuery rqt;
    QString usrId;

    qDebug() << this->nom;
    if(rqt.exec("SELECT UsrId FROM User Where Nom='" + this->nom + "'"))
    {
        rqt.next();
        usrId.setNum(rqt.value(0).toInt(), 10);

        qDebug() << usrId;
    }
    if(rqt.exec("DELETE FROM Score Where IdUser='" + usrId + "'"))
        QMessageBox::warning(this, "Reussite !", "Suppression effectuee !");

}

void MainWindow::on_actionAfficher_historique_triggered()
{
    afficherTexte* fenetre = new afficherTexte(2, this->BDD,this->nom, this);
    fenetre->show();
}

void MainWindow::on_actionPannes_automatiques_triggered()
{
    this->timer->start(5000);
}

void MainWindow::panneP11()
{
    if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getRempli())
    {
        int i;
        int moteurAlimente = 0;
        for(i = 1 ; i < 3 ; i++)
            if(a->moteur[0][i] == 1)
                moteurAlimente = i;
        if(moteurAlimente != 0)
        {
            a->moteur[0][moteurAlimente] = 0;
            switch (moteurAlimente) {

                case 1:
                    if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getPompe1().getEtat() == 1 && a->R[2].getRempli() && !a->V[4].getOuvert())
                        a->moteur[2][1] = 1;
                    break;

                case 2:
                    if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getPompe1().getEtat() == 1 && a->R[1].getRempli() && !a->V[4].getOuvert())
                        a->moteur[1][2] = 1;
                    break;
            }
        }
    }else if(a->R[0].getPompe1().getEtat() == 1 && a->R[0].getPompe2().getEtat() != 1)
    {
        a->moteur[0][0] = 0;
        if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getPompe1().getEtat() == 1 && a->R[2].getRempli() && !a->V[3].getOuvert() && a->moteur[2][1] != 1)
            a->moteur[2][0] = 1;
        else if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getPompe1().getEtat() == 1 && a->R[1].getRempli() && !a->V[2].getOuvert() && a->moteur[1][2] != 1)
            a->moteur[1][0] = 1;

    }
    a->R[0].getPompe1().panne();
    updateFenetre();
    if(!a->peutFonctionner())
    {
        decrementerNombreDeChrono();
        chrono = 0;
        on_actionR_initialiser_Simulation_triggered();
    }
    else if(a->actionNecessaire() && (int)chrono == 0)
        demarrerChrono();
    else if(!a->actionNecessaire() && (int)chrono != 0){
        time_t tmp;
        time(&tmp);
        if((int)(tmp - chrono) > 2)
            tempsTotalEcoule = tempsTotalEcoule + (int)(tmp - chrono);
        else
            decrementerNombreDeChrono();
        chrono = 0;
    }

}

void MainWindow::panneP12()
{ qDebug("Test 1\n");
    if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getRempli())
    { qDebug("Test 2\n");
        int moteurAlimente = 0;
        for(int i = 0 ; i < 3 ; i++)
            if(a->moteur[0][i] == 1)
                moteurAlimente = i;
        if(moteurAlimente == 0)
        {qDebug("Test 3\n");
            if(a->R[0].getPompe1().getEtat() != 1)
            {qDebug("Test 4\n");
                a->moteur[0][0] = 0;
                if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getPompe1().getEtat() == 1 && a->R[2].getRempli() && !a->V[3].getOuvert() && a->moteur[2][1] != 1)
                    a->moteur[2][0] = 1;
                else if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getPompe1().getEtat() == 1 && a->R[1].getRempli() && !a->V[2].getOuvert() && a->moteur[1][2] != 1)
                    a->moteur[1][0] = 1;
            }
        }else if(moteurAlimente == 1)
        {qDebug("Test 5\n");
            a->moteur[0][moteurAlimente] = 0;
            if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getPompe1().getEtat() == 1 && a->R[2].getRempli() && !a->V[4].getOuvert())
                a->moteur[2][1] = 1;
        }else{ qDebug("Test 6\n");
            a->moteur[0][moteurAlimente] = 0;
            if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getPompe1().getEtat() == 1 && a->R[1].getRempli() && !a->V[4].getOuvert())
                a->moteur[1][2] = 1;
        }
    }

   printf("Test 7\n");
  this->a->R[0].getPompe2().panne();
   // a->R[0].getPompe2().panne();
   //this->a->R[0].panneP2();
    qDebug("Valeur pompe : %d", this->a->R[0].getPompe2().getEtat() );
    qDebug("Test 8\n");
    updateFenetre();
    qDebug("Test 9\n");
    if(!a->peutFonctionner())
    {
        decrementerNombreDeChrono();
        chrono = 0;
        on_actionR_initialiser_Simulation_triggered();
    }
    else if(a->actionNecessaire() && (int)chrono == 0)
        demarrerChrono();
    else if(!a->actionNecessaire() && (int)chrono != 0){
        time_t tmp;
        time(&tmp);
        if((int)(tmp - chrono) > 2)
            tempsTotalEcoule = tempsTotalEcoule + (int)(tmp - chrono);
        else
            decrementerNombreDeChrono();
        chrono = 0;
    }
}

void MainWindow::panneP21()
{
    if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getRempli())
    {
        int i;
        int moteurAlimente = -1;
        for(i = 0 ; i < 3 ; i++)
            if(a->moteur[1][i] == 1 && i != 1)
                moteurAlimente = i;
        if(moteurAlimente != -1)
        {
            a->moteur[1][moteurAlimente] = 0;
            switch (moteurAlimente) {

                case 0:
                    if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getPompe1().getEtat() == 1 && a->R[2].getRempli() && !a->V[3].getOuvert())
                        a->moteur[2][0] = 1;
                    break;

                case 2:
                    if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getPompe1().getEtat() == 1 && a->R[0].getRempli() && !a->V[3].getOuvert())
                        a->moteur[0][2] = 1;
                    break;
            }
        }
    }else if(a->R[1].getPompe1().getEtat() == 1 && a->R[1].getPompe2().getEtat() != 1)
    {
        a->moteur[1][1] = 0;
        if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getPompe1().getEtat() == 1 && a->R[2].getRempli() && !a->V[4].getOuvert() && a->moteur[2][0] != 1)
            a->moteur[2][1] = 1;
        else if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getPompe1().getEtat() == 1 && a->R[0].getRempli() && !a->V[2].getOuvert() && a->moteur[0][2] != 1)
            a->moteur[0][1] = 1;

    }
    a->R[1].getPompe1().panne();
    updateFenetre();
    if(!a->peutFonctionner())
    {
        decrementerNombreDeChrono();
        chrono = 0;
        on_actionR_initialiser_Simulation_triggered();
    }
    else if(a->actionNecessaire() && (int)chrono == 0)
        demarrerChrono();
    else if(!a->actionNecessaire() && (int)chrono != 0){
        time_t tmp;
        time(&tmp);
        if((int)(tmp - chrono) > 2)
            tempsTotalEcoule = tempsTotalEcoule + (int)(tmp - chrono);
        else
            decrementerNombreDeChrono();
        chrono = 0;
    }
}

void MainWindow::panneP22()
{
    if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getRempli())
    {
        int i;
        int moteurAlimente = 1;
        for(i = 0 ; i < 3 ; i++)
            if(a->moteur[1][i] == 1 && i != 1)
                moteurAlimente = i;
        if(moteurAlimente == 1)
        {
            if(a->R[1].getPompe1().getEtat() != 1)
            {
                a->moteur[1][1] = 0;
                if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getPompe1().getEtat() == 1 && a->R[2].getRempli() && !a->V[4].getOuvert() && a->moteur[2][0] != 1)
                    a->moteur[2][1] = 1;
                else if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getPompe1().getEtat() == 1 && a->R[0].getRempli() && !a->V[2].getOuvert() && a->moteur[0][2] != 1)
                    a->moteur[0][1] = 1;
            }
        }else if(moteurAlimente == 0){
            a->moteur[1][moteurAlimente] = 0;
            if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getPompe1().getEtat() == 1 && a->R[2].getRempli() && !a->V[3].getOuvert())
                a->moteur[2][0] = 1;
        }else{
            a->moteur[1][moteurAlimente] = 0;
            if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getPompe1().getEtat() == 1 && a->R[0].getRempli() && !a->V[3].getOuvert())
                a->moteur[0][2] = 1;
        }

    }
    a->R[1].getPompe2().panne();
    updateFenetre();
    if(!a->peutFonctionner())
    {
        decrementerNombreDeChrono();
        chrono = 0;
        on_actionR_initialiser_Simulation_triggered();
    }
    else if(a->actionNecessaire() && (int)chrono == 0)
        demarrerChrono();
    else if(!a->actionNecessaire() && (int)chrono != 0){
        time_t tmp;
        time(&tmp);
        if((int)(tmp - chrono) > 2)
            tempsTotalEcoule = tempsTotalEcoule + (int)(tmp - chrono);
        else
            decrementerNombreDeChrono();
        chrono = 0;
    }
}

void MainWindow::panneP31()
{
    if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getRempli())
    {
        int i;
        int moteurAlimente = -1;
        for(i = 0 ; i < 2 ; i++)
            if(a->moteur[2][i] == 1)
                moteurAlimente = i;
        if(moteurAlimente != -1)
        {
            a->moteur[2][i] = 0;
            switch (i) {

                case 0:
                    if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getPompe1().getEtat() == 1 && a->R[1].getRempli() && !a->V[2].getOuvert())
                        a->moteur[1][0] = 1;
                    break;

                case 1:
                    if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getPompe1().getEtat() == 1 && a->R[0].getRempli() && !a->V[2].getOuvert())
                        a->moteur[0][1] = 1;
                    break;
            }
        }
    }else if(a->R[2].getPompe1().getEtat() == 1 && a->R[2].getPompe2().getEtat() != 1)
    {
        a->moteur[2][2] = 0;
        if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getPompe1().getEtat() == 1 && a->R[1].getRempli() && !a->V[4].getOuvert() && a->moteur[1][0] != 1)
            a->moteur[1][2] = 1;
        else if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getPompe1().getEtat() == 1 && a->R[0].getRempli() && !a->V[3].getOuvert() && a->moteur[0][1] != 1)
            a->moteur[0][2] = 1;

    }
    a->R[2].getPompe1().panne();
    updateFenetre();
    if(!a->peutFonctionner())
    {
        decrementerNombreDeChrono();
        chrono = 0;
        on_actionR_initialiser_Simulation_triggered();
    }
    else if(a->actionNecessaire() && (int)chrono == 0)
        demarrerChrono();
    else if(!a->actionNecessaire() && (int)chrono != 0){
        time_t tmp;
        time(&tmp);
        if((int)(tmp - chrono) > 2)
            tempsTotalEcoule = tempsTotalEcoule + (int)(tmp - chrono);
        else
            decrementerNombreDeChrono();
        chrono = 0;
    }
}

void MainWindow::panneP32()
{
    if(a->R[2].getPompe2().getEtat() == 1 && a->R[2].getRempli())
    {
        int moteurAlimente = 2;
        for(int i = 0 ; i < 2 ; i++)
            if(a->moteur[2][i] == 1)
                moteurAlimente = i;
        if(moteurAlimente == 2){
           if(a->R[2].getPompe1().getEtat() != 1)
           {
                a->moteur[2][2] = 0;
                if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getPompe1().getEtat() == 1 && a->R[1].getRempli() && !a->V[4].getOuvert() && a->moteur[1][0] != 1)
                    a->moteur[1][2] = 1;
                else if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getPompe1().getEtat() == 1 && a->R[0].getRempli() && !a->V[3].getOuvert() && a->moteur[0][1] != 1)
                    a->moteur[0][2] = 1;
           }
        }else if(moteurAlimente == 0){
            a->moteur[2][moteurAlimente] = 0;
            if(a->R[1].getPompe2().getEtat() == 1 && a->R[1].getPompe1().getEtat() == 1 && a->R[1].getRempli() && !a->V[2].getOuvert())
                a->moteur[1][0] = 1;
        }else{
            a->moteur[2][moteurAlimente] = 0;
            if(a->R[0].getPompe2().getEtat() == 1 && a->R[0].getPompe1().getEtat() == 1 && a->R[0].getRempli() && !a->V[2].getOuvert())
                a->moteur[0][1] = 1;
        }
    }
    a->R[2].getPompe2().panne();
    updateFenetre();
    if(!a->peutFonctionner())
    {
        decrementerNombreDeChrono();
        chrono = 0;
        on_actionR_initialiser_Simulation_triggered();
    }
    else if(a->actionNecessaire() && (int)chrono == 0)
        demarrerChrono();
    else if(!a->actionNecessaire() && (int)chrono != 0){
        time_t tmp;
        time(&tmp);
        if((int)(tmp - chrono) > 2)
            tempsTotalEcoule = tempsTotalEcoule + (int)(tmp - chrono);
        else
            decrementerNombreDeChrono();
        chrono = 0;
    }
}

void MainWindow::vidangeR1()
{
    if( !a->V[0].getOuvert() && a->R[1].getRempli() && a->nbReservoirVidange() != 3 && ( !a->R[1].getVidange() || (a->R[1].getVidange() && !a->V[1].getOuvert()) ) ){
        a->R[0].vidanger();
        a->R[0].setRempli(true);
    }else{
        if(a->R[0].getPompe1().getEtat() == 1 && a->R[0].getPompe2().getEtat() == 1){
            panneP11();
            panneP12();
            a->R[0].getPompe1().marche();
            a->R[0].getPompe2().marche();
        }else{
            if(a->R[0].getPompe1().getEtat() == 1){
                panneP11();
                a->R[0].getPompe1().marche();
            }
            if(a->R[0].getPompe2().getEtat() == 1){
                panneP12();
                a->R[0].getPompe2().marche();
            }
        }
        a->R[0].vidanger();
        cout << "1" << endl;
        updateFenetre();
        if(!a->V[0].getOuvert() && a->R[1].getVidange() && a->R[1].getRempli())
            vidangeR2();
    }
    cout << "2" << endl;
    updateFenetre();
    cout << "3" << endl;
    if(!a->peutFonctionner())
    {
        decrementerNombreDeChrono();
        chrono = 0;
        on_actionR_initialiser_Simulation_triggered();
    }
    else if(a->actionNecessaire() && (int)chrono == 0)
        demarrerChrono();
    else if(!a->actionNecessaire() && (int)chrono != 0){
        time_t tmp;
        time(&tmp);
        if((int)(tmp - chrono) > 2)
            tempsTotalEcoule = tempsTotalEcoule + (int)(tmp - chrono);
        else
            decrementerNombreDeChrono();
        chrono = 0;
    }
}

void MainWindow::vidangeR2()
{
    if( (!a->V[0].getOuvert() && a->R[0].getRempli() && !a->R[0].getVidange() ) || (!a->V[1].getOuvert() && a->R[2].getRempli() && !a->R[2].getVidange() ) )
    {
        a->R[1].vidanger();
        a->R[1].setRempli(true);
    }else{
        if(a->R[1].getPompe1().getEtat() == 1 && a->R[1].getPompe2().getEtat() == 1){
            panneP21();
            panneP22();
            a->R[1].getPompe1().marche();
            a->R[1].getPompe2().marche();
        }else{
            if(a->R[1].getPompe1().getEtat() == 1){
                panneP21();
                a->R[1].getPompe1().marche();
            }
            if(a->R[1].getPompe2().getEtat() == 1){
                panneP22();
                a->R[1].getPompe2().marche();
            }
        }
        a->R[1].vidanger();
        updateFenetre();
        if(!a->V[0].getOuvert() && a->R[0].getRempli() && a->R[0].getVidange())
            vidangeR1();
        if(!a->V[1].getOuvert() && a->R[2].getRempli() && a->R[2].getVidange())
            vidangeR3();
    }
    updateFenetre();
    if(!a->peutFonctionner())
    {
        decrementerNombreDeChrono();
        chrono = 0;
        on_actionR_initialiser_Simulation_triggered();
    }
    else if(a->actionNecessaire() && (int)chrono == 0)
        demarrerChrono();
    else if(!a->actionNecessaire() && (int)chrono != 0){
        time_t tmp;
        time(&tmp);
        if((int)(tmp - chrono) > 2)
            tempsTotalEcoule = tempsTotalEcoule + (int)(tmp - chrono);
        else
            decrementerNombreDeChrono();
        chrono = 0;
    }
}

void MainWindow::vidangeR3()
{
    if( !a->V[1].getOuvert() && a->R[1].getRempli() && a->nbReservoirVidange() != 3 && ( !a->R[1].getVidange() || (a->R[1].getVidange() && !a->V[0].getOuvert()) ) ){
        a->R[2].vidanger();
        a->R[2].setRempli(true);
    }else{
        if(a->R[2].getPompe1().getEtat() == 1 && a->R[2].getPompe2().getEtat() == 1){
            panneP31();
            panneP32();
            a->R[2].getPompe1().marche();
            a->R[2].getPompe2().marche();
        }else{
            if(a->R[2].getPompe1().getEtat() == 1){
                panneP31();
                a->R[2].getPompe1().marche();
            }
            if(a->R[2].getPompe2().getEtat() == 1){
                panneP32();
                a->R[2].getPompe2().marche();
            }
        }
        a->R[2].vidanger();
        updateFenetre();
        if(!a->V[1].getOuvert() && a->R[1].getVidange() && a->R[1].getRempli() )
            vidangeR2();
    }
    updateFenetre();
    if(!a->peutFonctionner())
    {
        decrementerNombreDeChrono();
        chrono = 0;
        on_actionR_initialiser_Simulation_triggered();
    }
    else if(a->actionNecessaire() && (int)chrono == 0)
        demarrerChrono();
    else if(!a->actionNecessaire() && (int)chrono != 0){
        time_t tmp;
        time(&tmp);
        if((int)(tmp - chrono) > 2)
            tempsTotalEcoule = tempsTotalEcoule + (int)(tmp - chrono);
        else
            decrementerNombreDeChrono();
        chrono = 0;
    }
}

void MainWindow::panneAlea()
{
    bool termine = false;
    int test;

    for(int i = 0; i < 9; i++)
        qDebug() << "ordre : " << i << " = " << ordrePanneAlea[i];
    do
    {
        test = ordrePanneAlea[9];
        qDebug() << "ordre panne alea[9] =" << ordrePanneAlea[9];
        qDebug() << "la valeur :" << ordrePanneAlea[test];
        switch(ordrePanneAlea[ordrePanneAlea[9]])
        {
            case 0:
                if(!this->a->R[0].getVidange())
                {
                    termine = true;
                    vidangeR1();
                }
                ordrePanneAlea[9]++;

                break;
            case 1:
                if(!this->a->R[1].getVidange())
                {
                    termine = true;
                    vidangeR2();
                }
                ordrePanneAlea[9]++;

                break;
            case 2:
                if(!this->a->R[2].getVidange())
                {
                    termine = true;
                    vidangeR3();
                }
                ordrePanneAlea[9]++;

                break;
            case 3:
            if(this->a->R[0].getPompe1().getEtat() != -1)
                {
                    termine = true;
                    panneP11();
                }
                ordrePanneAlea[9]++;

                break;
            case 4:
                if(this->a->R[0].getPompe2().getEtat() != -1)
                {
                    termine = true;
                    panneP12();
                }
                ordrePanneAlea[9]++;

                break;
            case 5:
                if(this->a->R[1].getPompe1().getEtat() != -1)
                {
                    termine = true;
                    panneP21();
                }
                ordrePanneAlea[9]++;

                break;
            case 6:
                if(this->a->R[1].getPompe2().getEtat() != -1)
                {
                    termine = true;
                    panneP22();
                }
                ordrePanneAlea[9]++;

                break;
            case 7:
                if(this->a->R[2].getPompe1().getEtat() != -1)
                {
                    termine = true;
                    panneP31();
                }
                ordrePanneAlea[9]++;

                break;
            case 8:
                if(this->a->R[2].getPompe2().getEtat() != -1)
                {
                    termine = true;
                    panneP32();
                }
                ordrePanneAlea[9]++;

                break;

        }
    } while(termine == false);
}
