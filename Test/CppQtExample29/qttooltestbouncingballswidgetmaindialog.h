#ifndef QTTOOLTESTBOUNCINGBALLSWIDGETMAINDIALOG_H
#define QTTOOLTESTBOUNCINGBALLSWIDGETMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
class QtToolTestBouncingBallsWidgetMainDialog;
}

class QtToolTestBouncingBallsWidgetMainDialog : public QDialog
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
