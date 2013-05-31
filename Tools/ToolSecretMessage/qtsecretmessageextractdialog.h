#ifndef QTSECRETMESSAGEEXTRACTDIALOG_H
#define QTSECRETMESSAGEEXTRACTDIALOG_H

#include <QDialog>

namespace Ui {
class QtSecretMessageExtractDialog;
}

class QtSecretMessageExtractDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtSecretMessageExtractDialog(QWidget *parent = 0);
    ~QtSecretMessageExtractDialog();
    
private:
    Ui::QtSecretMessageExtractDialog *ui;
};

#endif // QTSECRETMESSAGEEXTRACTDIALOG_H
