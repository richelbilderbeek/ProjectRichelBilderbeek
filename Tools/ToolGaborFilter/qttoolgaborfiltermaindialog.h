#ifndef QTTOOLGABORFILTERMAINDIALOG_H
#define QTTOOLGABORFILTERMAINDIALOG_H

#include <QDialog>

namespace Ui {
class QtToolGaborFilterMainDialog;
}

class QtToolGaborFilterMainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtToolGaborFilterMainDialog(QWidget *parent = 0);
    ~QtToolGaborFilterMainDialog();
    
private slots:
    void on_dial_angle_sliderMoved(int position);

    void on_slider_frequency_sliderMoved(int position);

    void on_slider_sigma_sliderMoved(int position);

private:
    Ui::QtToolGaborFilterMainDialog *ui;
};

#endif // QTTOOLGABORFILTERMAINDIALOG_H
