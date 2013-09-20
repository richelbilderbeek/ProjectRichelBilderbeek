#ifndef QTXENONZEROMAINDIALOG_H
#define QTXENONZEROMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"

#include "gamexenonzerofwd.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtXeNonZeroMainDialog;
}

namespace ribi {

class QtXeNonZeroMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  explicit QtXeNonZeroMainDialog(QWidget *parent = 0);
  QtXeNonZeroMainDialog(const QtXeNonZeroMainDialog&) = delete;
  QtXeNonZeroMainDialog operator=(const QtXeNonZeroMainDialog&) = delete;
  ~QtXeNonZeroMainDialog() noexcept;
  
private slots:
  void on_button_a_clicked();
  void on_button_d_clicked();
  void on_button_e_clicked();
  void on_button_s_clicked();
  void on_button_space_clicked();
  void on_button_w_clicked();

private:
  Ui::QtXeNonZeroMainDialog *ui;
  const boost::shared_ptr<xnz::Dialog> m_dialog;

  ///Displays the dialog
  void Display(const boost::shared_ptr<const xnz::Area> area);
};

} //~namespace ribi

#endif // QTXENONZEROMAINDIALOG_H
