#ifndef QTK3OPEENRIJMENUDIALOG_H
#define QTK3OPEENRIJMENUDIALOG_H

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

namespace Ui {
  class QtK3OpEenRijMenuDialog;
}
struct QtK3OpEenRijSelectPlayerWidget;

class QtK3OpEenRijMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtK3OpEenRijMenuDialog(QWidget *parent = 0);
  ~QtK3OpEenRijMenuDialog();

private:
  Ui::QtK3OpEenRijMenuDialog *ui;
  boost::shared_ptr<QtK3OpEenRijSelectPlayerWidget> m_select;

private slots:

  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

  #ifndef NDEBUG
  static void Test();
  #endif


  void on_button_instructions_clicked();
};

#endif // QTK3OPEENRIJMENUDIALOG_H
