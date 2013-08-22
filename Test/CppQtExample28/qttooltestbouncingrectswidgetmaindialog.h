#ifndef QTTOOLTESTBOUNCINGRECTSWIDGETMAINDIALOG_H
#define QTTOOLTESTBOUNCINGRECTSWIDGETMAINDIALOG_H

#include <QDialog>

namespace Ui {
class QtToolTestBouncingRectsWidgetMainDialog;
}

class QtToolTestBouncingRectsWidgetMainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtToolTestBouncingRectsWidgetMainDialog(QWidget *parent = 0);
    ~QtToolTestBouncingRectsWidgetMainDialog();
    
private:
    Ui::QtToolTestBouncingRectsWidgetMainDialog *ui;
};

#endif // QTTOOLTESTBOUNCINGRECTSWIDGETMAINDIALOG_H
