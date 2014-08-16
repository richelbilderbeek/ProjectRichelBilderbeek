#ifndef QTTESTPLANEMENUDIALOG_H
#define QTTESTPLANEMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtTestPlaneMenuDialog;
}

namespace ribi {

class QtTestPlaneMenuDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
  explicit QtTestPlaneMenuDialog(QWidget *parent = 0);
  QtTestPlaneMenuDialog(const QtTestPlaneMenuDialog&) = delete;
  QtTestPlaneMenuDialog& operator=(const QtTestPlaneMenuDialog&) = delete;
  ~QtTestPlaneMenuDialog() noexcept;
    
private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

  void on_button_investigate_accuracy_qwt_clicked();
  void on_button_investigate_accuracy_ribi_clicked();

private:
  Ui::QtTestPlaneMenuDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTTESTPLANEMENUDIALOG_H
