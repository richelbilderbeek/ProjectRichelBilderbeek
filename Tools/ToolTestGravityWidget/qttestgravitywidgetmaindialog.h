#ifndef TOOLTESTGRAVITYWIDGETMAINDIALOG_H
#define TOOLTESTGRAVITYWIDGETMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestGravityWidgetMainDialog;
}

class QtTestGravityWidgetMainDialog : public QDialog
{
  Q_OBJECT
    
public:
  explicit QtTestGravityWidgetMainDialog(QWidget *parent = 0);
  QtTestGravityWidgetMainDialog(const QtTestGravityWidgetMainDialog&) = delete;
  QtTestGravityWidgetMainDialog& operator=(const QtTestGravityWidgetMainDialog&) = delete;
  ~QtTestGravityWidgetMainDialog() noexcept;

private:
  Ui::QtTestGravityWidgetMainDialog *ui;
};

#endif // TOOLTESTGRAVITYWIDGETMAINDIALOG_H
