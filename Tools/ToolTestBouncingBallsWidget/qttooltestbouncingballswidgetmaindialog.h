#ifndef QTTOOLTESTBOUNCINGBALLSWIDGETMAINDIALOG_H
#define QTTOOLTESTBOUNCINGBALLSWIDGETMAINDIALOG_H

#include <QDialog>

namespace Ui {
class QtToolTestBouncingBallsWidgetMainDialog;
}

class QtToolTestBouncingBallsWidgetMainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtToolTestBouncingBallsWidgetMainDialog(QWidget *parent = 0);
    ~QtToolTestBouncingBallsWidgetMainDialog();
    
private:
    Ui::QtToolTestBouncingBallsWidgetMainDialog *ui;
};

#endif // QTTOOLTESTBOUNCINGBALLSWIDGETMAINDIALOG_H
