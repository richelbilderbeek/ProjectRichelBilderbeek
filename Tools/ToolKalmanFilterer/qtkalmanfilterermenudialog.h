#ifndef QTKALMANFILTERERMENUDIALOG_H
#define QTKALMANFILTERERMENUDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

#include "qthideandshowdialog.h"

///NEVER FORGET: Do never use forward declarations in header files parsed by MOC

namespace Ui {
  class QtKalmanFiltererMenuDialog;
}

class QtKalmanFiltererMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtKalmanFiltererMenuDialog(QWidget *parent = 0);
  ~QtKalmanFiltererMenuDialog();

protected:
  void changeEvent(QEvent *e);
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::QtKalmanFiltererMenuDialog *ui;

private slots:
  void on_button_about_clicked();
  void on_button_quit_clicked();
  void on_button_start_clicked();

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif
};

#endif // QTKALMANFILTERERMENUDIALOG_H
