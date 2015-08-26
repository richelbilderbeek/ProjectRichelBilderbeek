#ifndef QTPICTOCODEMENUDIALOG_H
#define QTPICTOCODEMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPicToCodeMenuDialog;
}


namespace ribi {
namespace p2c {

class QtPicToCodeMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPicToCodeMenuDialog(QWidget *parent = 0);
  QtPicToCodeMenuDialog(const QtPicToCodeMenuDialog&) = delete;
  QtPicToCodeMenuDialog& operator=(const QtPicToCodeMenuDialog&) = delete;
  ~QtPicToCodeMenuDialog() noexcept;

protected:


private:
  Ui::QtPicToCodeMenuDialog *ui;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_button_quit_clicked();
  void on_button_about_clicked();
  void on_button_start_clicked();
};

} //~namespace p2c
} //~namespace ribi

#endif // QTPICTOCODEMENUDIALOG_H
