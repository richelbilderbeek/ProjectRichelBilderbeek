#ifndef SOMEDIALOG_H
#define SOMEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
class SomeDialog;
}

class SomeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SomeDialog(QWidget *parent = 0);
    ~SomeDialog();
    
private:
    Ui::SomeDialog *ui;
};

#endif // SOMEDIALOG_H
