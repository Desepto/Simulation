#ifndef AIDE_H
#define AIDE_H

#include <QtWidgets/QDialog>

namespace Ui {
class Aide;
}

class Aide : public QDialog
{
    Q_OBJECT
    
public:
    explicit Aide(QWidget *parent = 0);
    ~Aide();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::Aide *ui;
};

#endif // AIDE_H
