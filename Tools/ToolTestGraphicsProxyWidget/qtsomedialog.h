#ifndef SOMEDIALOG_H
#define SOMEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtSomeDialog;
}

class QtSomeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtSomeDialog(QWidget *parent = 0);
    QtSomeDialog(const QtSomeDialog&) = delete;
    QtSomeDialog& operator=(const QtSomeDialog&) = delete;
    ~QtSomeDialog();
    
private:
    Ui::QtSomeDialog *ui;
};

#endif // SOMEDIALOG_H
