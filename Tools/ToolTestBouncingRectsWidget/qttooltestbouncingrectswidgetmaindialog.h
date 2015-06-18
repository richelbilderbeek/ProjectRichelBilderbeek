#ifndef QTTOOLTESTBOUNCINGRECTSWIDGETMAINDIALOG_H
#define QTTOOLTESTBOUNCINGRECTSWIDGETMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtToolTestBouncingRectsWidgetMainDialog;
}

class QtToolTestBouncingRectsWidgetMainDialog : public ribi::QtHideAndShowDialog
{
    Q_OBJECT
    
public:
    explicit QtToolTestBouncingRectsWidgetMainDialog(QWidget *parent = 0);
    QtToolTestBouncingRectsWidgetMainDialog(const QtToolTestBouncingRectsWidgetMainDialog&) = delete;
    QtToolTestBouncingRectsWidgetMainDialog& operator=(const QtToolTestBouncingRectsWidgetMainDialog&) = delete;
    ~QtToolTestBouncingRectsWidgetMainDialog() noexcept;
    
private:
    Ui::QtToolTestBouncingRectsWidgetMainDialog *ui;
};

#endif // QTTOOLTESTBOUNCINGRECTSWIDGETMAINDIALOG_H
