#ifndef TOOLTESTGRAVITYWIDGETMAINDIALOG_H
#define TOOLTESTGRAVITYWIDGETMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class ToolTestGravityWidgetMainDialog;
}

class ToolTestGravityWidgetMainDialog : public QDialog
{
  Q_OBJECT
    
public:
  explicit ToolTestGravityWidgetMainDialog(QWidget *parent = 0);
  ToolTestGravityWidgetMainDialog(const ToolTestGravityWidgetMainDialog&) = delete;
  ToolTestGravityWidgetMainDialog& operator=(const ToolTestGravityWidgetMainDialog&) = delete;
  ~ToolTestGravityWidgetMainDialog() noexcept;

private:
  Ui::ToolTestGravityWidgetMainDialog *ui;
};

#endif // TOOLTESTGRAVITYWIDGETMAINDIALOG_H
