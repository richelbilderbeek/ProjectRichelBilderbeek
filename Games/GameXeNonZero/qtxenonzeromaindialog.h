#ifndef QTXENONZEROMAINDIALOG_H
#define QTXENONZEROMAINDIALOG_H

#include <boost/shared_ptr.hpp>
#include <QDialog>

#include "gamexenonzerofwd.h"

namespace Ui {
  class QtXeNonZeroMainDialog;
}

class QtXeNonZeroMainDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit QtXeNonZeroMainDialog(QWidget *parent = 0);
  ~QtXeNonZeroMainDialog();
  
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

#endif // QTXENONZEROMAINDIALOG_H
