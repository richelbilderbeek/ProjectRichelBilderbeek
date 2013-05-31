#ifndef QTFILTEROPERATIONERMAINDIALOG_H
#define QTFILTEROPERATIONERMAINDIALOG_H

#include <QDialog>

namespace Ui {
class QtFilterOperationerMainDialog;
}

class QtFilterOperationerMainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtFilterOperationerMainDialog(QWidget *parent = 0);
    ~QtFilterOperationerMainDialog();
    
private:
    Ui::QtFilterOperationerMainDialog *ui;
};

#endif // QTFILTEROPERATIONERMAINDIALOG_H
