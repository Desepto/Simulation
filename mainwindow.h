#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "avion.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(Avion *a, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void panneP11();
    void panneP12();
    void panneP21();
    void panneP22();
    void panneP31();
    void panneP32();

    void vidangeR1();
    void vidangeR2();
    void vidangeR3();


private:
    Ui::MainWindow *ui;
    Avion* a;
};

#endif // MAINWINDOW_H
