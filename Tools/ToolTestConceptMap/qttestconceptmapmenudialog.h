#ifndef QTFILTEROPERATIONERMENUDIALOG_H
#define QTFILTEROPERATIONERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestConceptMapMenuDialog;
}

namespace ribi {

class QtTestConceptMapMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestConceptMapMenuDialog(QWidget *parent = 0);
  QtTestConceptMapMenuDialog(const QtTestConceptMapMenuDialog&) = delete;
  QtTestConceptMapMenuDialog& operator=(const QtTestConceptMapMenuDialog&) = delete;
  ~QtTestConceptMapMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

private:
  Ui::QtTestConceptMapMenuDialog *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // QTFILTEROPERATIONERMENUDIALOG_H
