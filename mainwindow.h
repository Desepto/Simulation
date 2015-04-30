#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "avion.h"
#include "fenetrepilote.h"
#include "aide.h"
#include "identification.h"
#include <QMessageBox>

class fenetrePilote;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(Avion *a, QString nom, QSqlDatabase BDD, QWidget *parent = 0);
    ~MainWindow();
    void addfenetre(fenetrePilote* f1);
    void updateFenetre();
    void updateReservoir();
    void updatePompe();
    void updateVanne();
    void updateMoteur();

public slots:
    void closeEvent(QCloseEvent *);

    void panneP11();
    void panneP12();
    void panneP21();
    void panneP22();
    void panneP31();
    void panneP32();

    void vidangeR1();
    void vidangeR2();
    void vidangeR3();


private slots:
    void on_actionLancer_Simulation_triggered();

    void on_actionStopper_simulation_triggered();

    void on_actionR_initialiser_Simulation_triggered();

    void on_actionChanger_Utilisateur_triggered();

    void on_actionAfficher_Aide_triggered();

    void on_actionSupprimer_historique_triggered();

private:
    Ui::MainWindow *ui;
    Avion* a;
    QString nom;
    fenetrePilote* f1;
    int chrono, tempsTotalEcoule, nombreDeChrono;
    QSqlDatabase BDD;
};

#endif // MAINWINDOW_H



