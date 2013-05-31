#ifndef TOOLTESTGRAVITYWIDGETMAINDIALOG_H
#define TOOLTESTGRAVITYWIDGETMAINDIALOG_H

#include <QDialog>

namespace Ui {
  class ToolTestGravityWidgetMainDialog;
}

class ToolTestGravityWidgetMainDialog : public QDialog
{
  Q_OBJECT
    
public:
  explicit ToolTestGravityWidgetMainDialog(QWidget *parent = 0);
  ~ToolTestGravityWidgetMainDialog();

private:
  Ui::ToolTestGravityWidgetMainDialog *ui;
};

#endif // TOOLTESTGRAVITYWIDGETMAINDIALOG_H
