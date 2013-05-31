#ifndef QTTOOLGABORFILTERMENUDIALOG_H
#define QTTOOLGABORFILTERMENUDIALOG_H

#include <QDialog>

namespace Ui {
class QtToolGaborFilterMenuDialog;
}

class QtToolGaborFilterMenuDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtToolGaborFilterMenuDialog(QWidget *parent = 0);
    ~QtToolGaborFilterMenuDialog();
    
private slots:
    void on_button_start_clicked();

    void on_button_about_clicked();

    void on_button_quit_clicked();

private:
    Ui::QtToolGaborFilterMenuDialog *ui;
};

#endif // QTTOOLGABORFILTERMENUDIALOG_H
