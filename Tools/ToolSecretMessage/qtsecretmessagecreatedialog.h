#ifndef QTSECRETMESSAGECREATEDIALOG_H
#define QTSECRETMESSAGECREATEDIALOG_H

#include <QDialog>

namespace Ui {
class QtSecretMessageCreateDialog;
}

class QtSecretMessageCreateDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtSecretMessageCreateDialog(QWidget *parent = 0);
    ~QtSecretMessageCreateDialog();
    
private slots:

    void on_button_load_original_clicked();

private:
    Ui::QtSecretMessageCreateDialog *ui;
};

#endif // QTSECRETMESSAGECREATEDIALOG_H
