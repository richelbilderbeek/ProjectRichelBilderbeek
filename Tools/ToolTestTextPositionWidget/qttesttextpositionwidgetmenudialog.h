#ifndef QTTESTTEXTPOSITIONWIDGETMENUDIALOG_H
#define QTTESTTEXTPOSITIONWIDGETMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestTextPositionWidgetMenuDialog;
}

namespace ribi {

class QtTestTextPositionWidgetMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestTextPositionWidgetMenuDialog(QWidget *parent = 0);
  QtTestTextPositionWidgetMenuDialog(const QtTestTextPositionWidgetMenuDialog&) = delete;
  QtTestTextPositionWidgetMenuDialog& operator=(const QtTestTextPositionWidgetMenuDialog&) = delete;
  ~QtTestTextPositionWidgetMenuDialog() noexcept;

protected:
  
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtTestTextPositionWidgetMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();
};

} //~namespace ribi

#endif // QTTESTTEXTPOSITIONWIDGETMENUDIALOG_H
