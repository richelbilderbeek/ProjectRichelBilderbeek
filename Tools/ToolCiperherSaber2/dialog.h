#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
private slots:


    void on_pbSelIF_clicked();

    void on_pbSelOF_clicked();

    void on_pbEncrypt_clicked();

    void on_pbDecrypt_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
