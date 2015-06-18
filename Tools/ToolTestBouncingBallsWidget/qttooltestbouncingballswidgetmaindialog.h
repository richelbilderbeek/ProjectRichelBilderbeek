#ifndef QTTOOLTESTBOUNCINGBALLSWIDGETMAINDIALOG_H
#define QTTOOLTESTBOUNCINGBALLSWIDGETMAINDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
class QtToolTestBouncingBallsWidgetMainDialog;
}

class QtToolTestBouncingBallsWidgetMainDialog : public ribi::QtHideAndShowDialog
{
    Q_OBJECT
    
public:
    explicit QtToolTestBouncingBallsWidgetMainDialog(QWidget *parent = 0);
    QtToolTestBouncingBallsWidgetMainDialog(const QtToolTestBouncingBallsWidgetMainDialog&) = delete;
    QtToolTestBouncingBallsWidgetMainDialog& operator=(const QtToolTestBouncingBallsWidgetMainDialog&) = delete;
    ~QtToolTestBouncingBallsWidgetMainDialog();
    
private:
    Ui::QtToolTestBouncingBallsWidgetMainDialog *ui;
};

#endif // QTTOOLTESTBOUNCINGBALLSWIDGETMAINDIALOG_H
