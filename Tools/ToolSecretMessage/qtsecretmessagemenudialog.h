#ifndef QTSECRETMESSAGEMENUDIALOG_H
#define QTSECRETMESSAGEMENUDIALOG_H

#include "qthideandshowdialog.h"

namespace Ui {
  class QtSecretMessageMenuDialog;
}

namespace ribi {
namespace sema {

class QtMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMenuDialog(QWidget *parent = 0);
  QtMenuDialog(const QtMenuDialog&) = delete;
  QtMenuDialog& operator=(const QtMenuDialog&) = delete;
  ~QtMenuDialog() noexcept;

private slots:
  void on_button_about_clicked();
  void on_button_create_clicked();
  void on_button_quit_clicked();
  void on_button_extract_clicked();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private:
  Ui::QtSecretMessageMenuDialog *ui;
};

} //~namespace sema
} //~namespace ribi

#endif // QTSECRETMESSAGEMENUDIALOG_H
