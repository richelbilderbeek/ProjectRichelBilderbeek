#ifndef QTSTAIRCASECARDCREATORMENUDIALOG_H
#define QTSTAIRCASECARDCREATORMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtStaircaseCardCreatorMenuDialog;
}

namespace ribi {
namespace scc {

class QtStaircaseCardCreatorMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtStaircaseCardCreatorMenuDialog(QWidget *parent = 0) noexcept;
  QtStaircaseCardCreatorMenuDialog(const QtStaircaseCardCreatorMenuDialog&) = delete;
  QtStaircaseCardCreatorMenuDialog& operator=(const QtStaircaseCardCreatorMenuDialog&) = delete;
  ~QtStaircaseCardCreatorMenuDialog() noexcept;

private:
  Ui::QtStaircaseCardCreatorMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace c2h
} //~namespace ribi

#endif // QTSTAIRCASECARDCREATORMENUDIALOG_H
